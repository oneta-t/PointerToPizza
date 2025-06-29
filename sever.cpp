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
