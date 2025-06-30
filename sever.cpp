#include "server.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

// سازنده سرور
Server::Server(QObject *parent) : QTcpServer(parent) {}

// شروع به کار سرور روی پورت مشخص
bool Server::startServer(quint16 port) {
    if (!listen(QHostAddress::Any, port)) {
        qCritical() << "Server could not start:" << errorString();
        return false;
    }
    qDebug() << "Server started on port" << port;
    return true;
}

// مدیریت اتصالات ورودی جدید
void Server::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *client = new QTcpSocket(this);
    if (!client->setSocketDescriptor(socketDescriptor)) {
        qWarning() << "Failed to set socket descriptor";
        delete client;
        return;
    }

    clients.insert(socketDescriptor, client);
    connect(client, &QTcpSocket::readyRead, this, &Server::readClientData);
    connect(client, &QTcpSocket::disconnected, this, &Server::clientDisconnected);
    qDebug() << "New client connected:" << socketDescriptor;
}

//خواندن داده های ارسالی از کلاینت
void Server::readClientData() {
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (!client) return;

    QByteArray data = client->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        QJsonObject response;
        response["status"] = "error";
        response["message"] = "Invalid JSON";
        client->write(QJsonDocument(response).toJson());
        return;
    }

    QJsonObject json = doc.object();
    QString type = json["type"].toString();

    // هدایت درخواست به تابع مناسب بر اساس نوع
    if (type == "register") {
        handleRegister(json, client);
    } else if (type == "login") {
        handleLogin(json, client);
    } else if (type == "order") {
        handleOrder(json, client);
    } else if (type == "get_restaurants") {
        handleGetRestaurants(client);
    } else if (type == "get_menu") {
        handleGetMenu(json, client);
    } else if (type == "get_my_order") {
        handleGetMyOrders(client);
    } else if (type == "change_order_status") {
        handleChangeOrderStatus(json, client);
    } else if (type == "get_orders_for_restuarant") {
        handleGetOrdersForRestaurant(client);
    } else if (type == "add_menu_item") {
        handleAddMenuItem(json, client);
    } else {
        QJsonObject response;
        response["status"] = "error";
        response["message"] = "Unknown request type";
        client->write(QJsonDocument(response).toJson());
    }
}

// مدیریت قطع ارتباط کلاینت
void Server::clientDisconnected() {
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (!client) return;

    qintptr descriptor = clients.key(client);
    clients.remove(descriptor);
    clientUserIds.remove(descriptor);
    client->deleteLater();
    qDebug() << "Client disconnected:" << descriptor;
}

// پردازش درخواست ثبت نام
void Server::handleRegister(const QJsonObject& json, QTcpSocket* client) {
    QString username = json["username"].toString();
    QString password = json["password"].toString();
    QString role = json["role"].toString("customer");

    QJsonObject response;
    if (userRepo.userExists(username)) {
        response["status"] = "error";
        response["message"] = "Username already exists";
    } else if (userRepo.addUser(username, password, role)) {
        response["status"] = "success";
        response["message"] = "Registered successfully";
    } else {
        response["status"] = "error";
        response["message"] = "Registration failed";
    }

    client->write(QJsonDocument(response).toJson());
}

// پردازش درخواست ورود
void Server::handleLogin(const QJsonObject& json, QTcpSocket* client) {
    QString username = json["username"].toString();
    QString password = json["password"].toString();
    int userId;
    QString role;

    QJsonObject response;
    if (userRepo.validateLogin(username, password, userId, role)) {
        clientUserIds[client->socketDescriptor()] = userId;
        response["status"] = "success";
        response["message"] = "Login successful";
        response["user_id"] = userId;
        response["role"] = role;
    } else {
        response["status"] = "error";
        response["message"] = "Invalid username or password";
    }

    client->write(QJsonDocument(response).toJson());
}

void Server::handleGetRestaurants(QTcpSocket* client) {
    QSqlQuery query(Database::instance().getConnection());
    QJsonArray restaurantArray;

    if (query.exec("SELECT id, name FROM restaurants WHERE status = 'approved'")) {
        while (query.next()) {
            QJsonObject rest;
            rest["id"] = query.value("id").toInt();
            rest["name"] = query.value("name").toString();
            restaurantArray.append(rest);
        }
        QJsonObject response;
        response["status"] = "success";
        response["restaurants"] = restaurantArray;
        client->write(QJsonDocument(response).toJson());
    } else {
        QJsonObject response {
            {"status", "error"},
            {"message", "Could not fetch restaurants"}
        };
        client->write(QJsonDocument(response).toJson());
    }
}

void Server::handleGetMenu(const QJsonObject& json, QTcpSocket* client) {
    int restaurantId = json["restaurant_id"].toInt();
    QSqlQuery query(Database::instance().getConnection());
    QJsonArray menuArray;

    query.prepare("SELECT id, name, price FROM menu_items WHERE restaurant_id = :rid");
    query.bindValue(":rid", restaurantId);
    if (query.exec()) {
        while (query.next()) {
            QJsonObject item;
            item["item_id"] = query.value("id").toInt();
            item["name"] = query.value("name").toString();
            item["price"] = query.value("price").toDouble();
            menuArray.append(item);
        }
        QJsonObject response;
        response["status"] = "success";
        response["menu"] = menuArray;
        client->write(QJsonDocument(response).toJson());
    } else {
        QJsonObject response {
            {"status", "error"},
            {"message", "Failed to get menu"}
        };
        client->write(QJsonDocument(response).toJson());
    }
}

// پردازش درخواست سفارش
void Server::handleOrder(const QJsonObject& json, QTcpSocket* client) {
    int userId = clientUserIds.value(client->socketDescriptor(), -1);
    if (userId == -1) {
        QJsonObject response {{"status", "error"}, {"message", "Not logged in"}};
        client->write(QJsonDocument(response).toJson());
        return;
    }

    int restaurantId = json["restaurant_id"].toInt();
    QJsonArray items = json["items"].toArray();

    QSqlQuery orderQuery(Database::instance().getConnection());
    orderQuery.prepare("INSERT INTO orders (user_id, restaurant_id, status) "
                       "VALUES (:user_id, :restaurant_id, 'pending')");
    orderQuery.bindValue(":user_id", userId);
    orderQuery.bindValue(":restaurant_id", restaurantId);

    QJsonObject response;

    if (!orderQuery.exec()) {
        response["status"] = "error";
        response["message"] = "Failed to create order: " + orderQuery.lastError().text();
        client->write(QJsonDocument(response).toJson());
        return;
    }

    int orderId = orderQuery.lastInsertId().toInt();
    bool success = true;

    // ثبت آیتم های سفارش
    for (const QJsonValue& val : items) {
        QJsonObject item = val.toObject();
        int itemId = item["item_id"].toInt();
        int qty = item["quantity"].toInt();

        QSqlQuery itemQuery(Database::instance().getConnection());
        itemQuery.prepare("INSERT INTO order_items (order_id, item_id, quantity) "
                          "VALUES (:order_id, :item_id, :qty)");
        itemQuery.bindValue(":order_id", orderId);
        itemQuery.bindValue(":item_id", itemId);
        itemQuery.bindValue(":qty", qty);

        if (!itemQuery.exec()) {
            qWarning() << "Insert item failed:" << itemQuery.lastError().text();
            success = false;
        }
    }

    if (!success) {
        response["status"] = "error";
        response["message"] = "Some order items failed to insert";
    } else {
        response["status"] = "success";
        response["message"] = "Order placed successfully";
        response["order_id"] = orderId;

        // ارسال نوتیفیکیشن به رستوران
        QString notification = QString("{\"type\":\"new_order\",\"order_id\":%1}")
                                   .arg(orderId);
        notifyRestaurant(restaurantId, notification);
    }

    client->write(QJsonDocument(response).toJson());
}

void Server::handleGetMyOrders(QTcpSocket* client) {
    int userId = clientUserIds.value(client->socketDescriptor(), -1);
    QJsonObject response;

    if (userId == -1) {
        response["status"] = "error";
        response["message"] = "Not logged in";
        client->write(QJsonDocument(response).toJson());
        return;
    }

    QSqlQuery query(Database::instance().getConnection());
    query.prepare(R"(
        SELECT orders.order_id, restaurants.name, orders.status, orders.create_at
        FROM orders
        JOIN restaurants ON orders.restaurant_id = restaurants.id
        WHERE orders.user_id = :uid
        ORDER BY orders.create_at DESC
    )");
    query.bindValue(":uid", userId);

    QJsonArray orderArray;
    if (query.exec()) {
        while (query.next()) {
            QJsonObject order;
            order["order_id"] = query.value("order_id").toInt();
            order["restaurant_name"] = query.value("name").toString();
            order["status"] = query.value("status").toString();
            order["date"] = query.value("create_at").toString();
            orderArray.append(order);
        }
        response["status"] = "success";
        response["orders"] = orderArray;
    } else {
        response["status"] = "error";
        response["message"] = "Failed to retrieve orders";
    }

    client->write(QJsonDocument(response).toJson());
}

void Server::handleChangeOrderStatus(const QJsonObject& json, QTcpSocket* client) {
    int userId = clientUserIds.value(client->socketDescriptor(), -1);
    int orderId = json["order_id"].toInt();
    QString newStatus = json["new_status"].toString();

    QJsonObject response;

    if (userId == -1) {
        response["status"] = "error";
        response["message"] = "Not logged in";
        client->write(QJsonDocument(response).toJson());
        return;
    }

    // بررسی اینکه این سفارش مال رستورانی هست که این کاربر صاحبشه
    QSqlQuery verify(Database::instance().getConnection());
    verify.prepare(R"(
        SELECT o.user_id
        FROM orders o
        JOIN restaurants r ON o.restaurant_id = r.id
        WHERE o.order_id = :oid AND r.owner_id = :uid
    )");
    verify.bindValue(":oid", orderId);
    verify.bindValue(":uid", userId);

    if (verify.exec() && verify.next()) {
        int customerId = verify.value("user_id").toInt();

        QSqlQuery update(Database::instance().getConnection());
        update.prepare("UPDATE orders SET status = :status WHERE order_id = :oid");
        update.bindValue(":status", newStatus);
        update.bindValue(":oid", orderId);

        if (update.exec()) {
            response["status"] = "success";
            response["message"] = "Order updated";

            // ارسال نوتیف به مشتری
            for (auto it = clientUserIds.begin(); it != clientUserIds.end(); ++it) {
                if (it.value() == customerId) {
                    QTcpSocket* customerClient = clients[it.key()];
                    if (customerClient) {
                        QJsonObject notif {
                            {"type", "order_status_update"},
                            {"order_id", orderId},
                            {"new_status", newStatus}
                        };
                        customerClient->write(QJsonDocument(notif).toJson());
                    }
                }
            }
        } else {
            response["status"] = "error";
            response["message"] = "DB update failed";
        }
    } else {
        response["status"] = "error";
        response["message"] = "Unauthorized or order not found";
    }

    client->write(QJsonDocument(response).toJson());
}

void Server::handleGetOrdersForRestaurant(QTcpSocket* client) {
    int ownerId = clientUserIds.value(client->socketDescriptor(), -1);
    QJsonObject response;

    if (ownerId == -1) {
        response["status"] = "error";
        response["message"] = "Not logged in";
        client->write(QJsonDocument(response).toJson());
        return;
    }

    QSqlQuery restQuery(Database::instance().getConnection());
    restQuery.prepare("SELECT id FROM restaurants WHERE owner_id = :oid AND status = 'approved'");
    restQuery.bindValue(":oid", ownerId);
    if (!restQuery.exec() || !restQuery.next()) {
        response["status"] = "error";
        response["message"] = "Restaurant not found";
        client->write(QJsonDocument(response).toJson());
        return;
    }

    int restId = restQuery.value("id").toInt();

    QSqlQuery orderQuery(Database::instance().getConnection());
    orderQuery.prepare("SELECT order_id, user_id, status FROM orders WHERE restaurant_id = :rid ORDER BY order_id DESC");
    orderQuery.bindValue(":rid", restId);

    QJsonArray ordersArray;
    if (orderQuery.exec()) {
        while (orderQuery.next()) {
            int orderId = orderQuery.value("order_id").toInt();
            int customerId = orderQuery.value("user_id").toInt();
            QString status = orderQuery.value("status").toString();

            QJsonArray itemArray;
            QSqlQuery items(Database::instance().getConnection());
            items.prepare(R"(
                SELECT oi.item_id, mi.name, oi.quantity
                FROM order_items oi
                JOIN menu_items mi ON oi.item_id = mi.id
                WHERE oi.order_id = :oid
            )");
            items.bindValue(":oid", orderId);
            items.exec();
            while (items.next()) {
                QJsonObject item;
                item["item_id"] = items.value("item_id").toInt();
                item["name"] = items.value("name").toString();
                item["quantity"] = items.value("quantity").toInt();
                itemArray.append(item);
            }

            QJsonObject orderObj;
            orderObj["order_id"] = orderId;
            orderObj["customer_id"] = customerId;
            orderObj["status"] = status;
            orderObj["items"] = itemArray;

            ordersArray.append(orderObj);
        }

        response["status"] = "success";
        response["orders"] = ordersArray;
    } else {
        response["status"] = "error";
        response["message"] = "Failed to fetch orders";
    }

    client->write(QJsonDocument(response).toJson());
}

void Server::handleAddMenuItem(const QJsonObject& json, QTcpSocket* client) {
    int ownerId = clientUserIds.value(client->socketDescriptor(), -1);
    QString name = json["name"].toString();
    double price = json["price"].toDouble();

    QJsonObject response;
    if (ownerId == -1 || name.isEmpty() || price <= 0) {
        response["status"] = "error";
        response["message"] = "Invalid data";
        client->write(QJsonDocument(response).toJson());
        return;
    }

    QSqlQuery restQuery(Database::instance().getConnection());
    restQuery.prepare("SELECT id FROM restaurants WHERE owner_id = :oid AND status = 'approved'");
    restQuery.bindValue(":oid", ownerId);
    if (!restQuery.exec() || !restQuery.next()) {
        response["status"] = "error";
        response["message"] = "Restaurant not found or not approved";
        client->write(QJsonDocument(response).toJson());
        return;
    }

    int restId = restQuery.value("id").toInt();

    QSqlQuery add(Database::instance().getConnection());
    add.prepare("INSERT INTO menu_items (restaurant_id, name, price) VALUES (:rid, :name, :price)");
    add.bindValue(":rid", restId);
    add.bindValue(":name", name);
    add.bindValue(":price", price);

    if (add.exec()) {
        response["status"] = "success";
        response["message"] = "Item added";
    } else {
        response["status"] = "error";
        response["message"] = "Insert failed";
    }

    client->write(QJsonDocument(response).toJson());
}

// ارسال اطلاعیه به رستوران
void Server::notifyRestaurant(int restaurantId, const QString& message) {
    QSqlQuery query(Database::instance().getConnection());
    query.prepare("SELECT owner_id FROM restaurants WHERE id = :restaurant_id");
    query.bindValue(":restaurant_id", restaurantId);
    if (query.exec() && query.next()) {

        // یافتن تمام کلاینت های متصل به این رستوران
        int ownerId = query.value("owner_id").toInt();
        for (auto it = clientUserIds.constBegin(); it != clientUserIds.constEnd(); ++it) {
            if (it.value() == ownerId) {
                QTcpSocket *client = clients.value(it.key());
                if (client) {
                    client->write(message.toUtf8());
                }
            }
        }
    }
}
