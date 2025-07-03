#include <QCoreApplication>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QTimer>

class TestClient : public QObject {
    Q_OBJECT
public:
    TestClient() : socket(this) {
        connect(&socket, &QTcpSocket::connected, this, &TestClient::onConnected);
        connect(&socket, &QTcpSocket::readyRead, this, &TestClient::onReadyRead);
        connect(&socket, &QTcpSocket::disconnected, this, &TestClient::onDisconnected);
        connect(&socket, &QTcpSocket::errorOccurred, this, &TestClient::onErrorOccurred);
    }

    void start() {
        qDebug() << "Connecting to server...";
        socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
    }

private slots:
    void onConnected() {
        qDebug() << "Connected to server.";
        runTests();
    }

    void onReadyRead() {
        QByteArray data = socket.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isNull()) {
            qDebug() << "Server response:" << doc.toJson(QJsonDocument::Indented);
        } else {
            qDebug() << "Invalid JSON response received.";
        }
        currentTest++;
        runTests();
    }

    void onDisconnected() {
        qDebug() << "Disconnected from server.";
        QCoreApplication::quit();
    }

    void onErrorOccurred(QAbstractSocket::SocketError socketError) {
        qDebug() << "Socket error:" << socket.errorString();
        QCoreApplication::quit();
    }

private:
    void runTests() {
        QJsonObject request;
        switch (currentTest) {
        case 0: // Test register (valid customer)
            qDebug() << "Testing register (valid customer)...";
            request.insert("type", "register");
            request.insert("username", "testcustomer");
            request.insert("password", "pass123");
            request.insert("role", "customer");
            break;
        case 1: // Test register (duplicate username)
            qDebug() << "Testing register (duplicate username)...";
            request.insert("type", "register");
            request.insert("username", "testcustomer");
            request.insert("password", "pass123");
            request.insert("role", "customer");
            break;
        case 2: // Test register (invalid data)
            qDebug() << "Testing register (invalid data)...";
            request.insert("type", "register");
            request.insert("username", "");
            request.insert("password", "pass123");
            break;
        case 3: // Test login (valid customer)
            qDebug() << "Testing login (valid customer)...";
            request.insert("type", "login");
            request.insert("username", "testcustomer");
            request.insert("password", "pass123");
            break;
        case 4: // Test login (invalid credentials)
            qDebug() << "Testing login (invalid credentials)...";
            request.insert("type", "login");
            request.insert("username", "testcustomer");
            request.insert("password", "wrongpass");
            break;
        case 5: // Test register (restaurant owner)
            qDebug() << "Testing register (restaurant owner)...";
            request.insert("type", "register");
            request.insert("username", "testowner");
            request.insert("password", "pass123");
            request.insert("role", "restaurant_owner");
            break;
        case 6: // Test login (restaurant owner)
            qDebug() << "Testing login (restaurant owner)...";
            request.insert("type", "login");
            request.insert("username", "testowner");
            request.insert("password", "pass123");
            break;
        case 7: // Test add_restaurant (valid)
            qDebug() << "Testing add_restaurant (valid)...";
            request.insert("type", "add_restaurant");
            request.insert("name", "Test Restaurant");
            break;
        case 8: // Test add_restaurant (invalid: not logged in)
            qDebug() << "Testing add_restaurant (invalid: not logged in)...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "add_restaurant");
                req.insert("name", "Test Restaurant");
                socket.write(QJsonDocument(req).toJson());
            });
            return;
        case 9: // Test register (admin)
            qDebug() << "Testing register (admin)...";
            request.insert("type", "register");
            request.insert("username", "testadmin");
            request.insert("password", "pass123");
            request.insert("role", "admin");
            break;
        case 10: // Test login (admin)
            qDebug() << "Testing login (admin)...";
            request.insert("type", "login");
            request.insert("username", "testadmin");
            request.insert("password", "pass123");
            break;
        case 11: // Test approve_restaurant (valid)
            qDebug() << "Testing approve_restaurant (valid)...";
            request.insert("type", "approve_restaurant");
            request.insert("restaurant_id", 1);
            request.insert("status", "approved");
            break;
        case 12: // Test approve_restaurant (invalid: not admin)
            qDebug() << "Testing approve_restaurant (invalid: not admin)...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "login");
                req.insert("username", "testcustomer");
                req.insert("password", "pass123");
                socket.write(QJsonDocument(req).toJson());
                QTimer::singleShot(2000, this, [=]() {
                    QJsonObject req2;
                    req2.insert("type", "approve_restaurant");
                    req2.insert("restaurant_id", 1);
                    req2.insert("status", "approved");
                    socket.write(QJsonDocument(req2).toJson());
                });
            });
            return;
        case 13: // Test get_restaurants
            qDebug() << "Testing get_restaurants...";
            request.insert("type", "get_restaurants");
            break;
        case 14: // Test add_menu_item (valid)
            qDebug() << "Testing add_menu_item (valid)...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "login");
                req.insert("username", "testowner");
                req.insert("password", "pass123");
                socket.write(QJsonDocument(req).toJson());
                QTimer::singleShot(2000, this, [=]() {
                    QJsonObject req2;
                    req2.insert("type", "add_menu_item");
                    req2.insert("name", "Pizza");
                    req2.insert("price", 10.99);
                    socket.write(QJsonDocument(req2).toJson());
                });
            });
            return;
        case 15: // Test get_menu
            qDebug() << "Testing get_menu...";
            request.insert("type", "get_menu");
            request.insert("restaurant_id", 1);
            break;
        case 16: // Test edit_menu_item (valid)
            qDebug() << "Testing edit_menu_item (valid)...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "login");
                req.insert("username", "testowner");
                req.insert("password", "pass123");
                socket.write(QJsonDocument(req).toJson());
                QTimer::singleShot(2000, this, [=]() {
                    QJsonObject req2;
                    req2.insert("type", "edit_menu_item");
                    req2.insert("item_id", 1);
                    req2.insert("name", "Updated Pizza");
                    req2.insert("price", 12.99);
                    socket.write(QJsonDocument(req2).toJson());
                });
            });
            return;
        case 17: // Test delete_menu_item (valid)
            qDebug() << "Testing delete_menu_item (valid)...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "login");
                req.insert("username", "testowner");
                req.insert("password", "pass123");
                socket.write(QJsonDocument(req).toJson());
                QTimer::singleShot(2000, this, [=]() {
                    QJsonObject req2;
                    req2.insert("type", "delete_menu_item");
                    req2.insert("item_id", 1);
                    socket.write(QJsonDocument(req2).toJson());
                });
            });
            return;
        case 18: // Test order (valid)
            qDebug() << "Testing order (valid)...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "login");
                req.insert("username", "testcustomer");
                req.insert("password", "pass123");
                socket.write(QJsonDocument(req).toJson());
                QTimer::singleShot(2000, this, [=]() {
                    QJsonObject item;
                    item.insert("item_id", 1);
                    item.insert("quantity", 2);
                    QJsonArray items;
                    items.append(item);
                    QJsonObject req2;
                    req2.insert("type", "order");
                    req2.insert("restaurant_id", 1);
                    req2.insert("items", items);
                    socket.write(QJsonDocument(req2).toJson());
                });
            });
            return;
        case 19: // Test get_my_orders
            qDebug() << "Testing get_my_orders...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "login");
                req.insert("username", "testcustomer");
                req.insert("password", "pass123");
                socket.write(QJsonDocument(req).toJson());
                QTimer::singleShot(2000, this, [=]() {
                    QJsonObject req2;
                    req2.insert("type", "get_my_orders");
                    socket.write(QJsonDocument(req2).toJson());
                });
            });
            return;
        case 20: // Test change_order_status (valid)
            qDebug() << "Testing change_order_status (valid)...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "login");
                req.insert("username", "testowner");
                req.insert("password", "pass123");
                socket.write(QJsonDocument(req).toJson());
                QTimer::singleShot(2000, this, [=]() {
                    QJsonObject req2;
                    req2.insert("type", "change_order_status");
                    req2.insert("order_id", 1);
                    req2.insert("new_status", "preparing");
                    socket.write(QJsonDocument(req2).toJson());
                });
            });
            return;
        case 21: // Test get_orders_for_restaurant
            qDebug() << "Testing get_orders_for_restaurant...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "login");
                req.insert("username", "testowner");
                req.insert("password", "pass123");
                socket.write(QJsonDocument(req).toJson());
                QTimer::singleShot(2000, this, [=]() {
                    QJsonObject req2;
                    req2.insert("type", "get_orders_for_restaurant");
                    socket.write(QJsonDocument(req2).toJson());
                });
            });
            return;
        case 22: // Test rate_order (valid)
            qDebug() << "Testing rate_order (valid)...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "login");
                req.insert("username", "testcustomer");
                req.insert("password", "pass123");
                socket.write(QJsonDocument(req).toJson());
                QTimer::singleShot(2000, this, [=]() {
                    QJsonObject req2;
                    req2.insert("type", "rate_order");
                    req2.insert("order_id", 1);
                    req2.insert("rating", 5);
                    req2.insert("comment", "Great food!");
                    socket.write(QJsonDocument(req2).toJson());
                });
            });
            return;
        case 23: // Test get_ratings
            qDebug() << "Testing get_ratings...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "login");
                req.insert("username", "testowner");
                req.insert("password", "pass123");
                socket.write(QJsonDocument(req).toJson());
                QTimer::singleShot(2000, this, [=]() {
                    QJsonObject req2;
                    req2.insert("type", "get_ratings");
                    req2.insert("restaurant_id", 1);
                    socket.write(QJsonDocument(req2).toJson());
                });
            });
            return;
        case 24: // Test block_user (valid)
            qDebug() << "Testing block_user (valid)...";
            socket.disconnectFromHost();
            socket.connectToHost("127.0.0.1", 12345); // تغییر به 127.0.0.1
            QTimer::singleShot(2000, this, [=]() {
                QJsonObject req;
                req.insert("type", "login");
                req.insert("username", "testadmin");
                req.insert("password", "pass123");
                socket.write(QJsonDocument(req).toJson());
                QTimer::singleShot(2000, this, [=]() {
                    QJsonObject req2;
                    req2.insert("type", "block_user");
                    req2.insert("user_id", 1);
                    req2.insert("block", true);
                    socket.write(QJsonDocument(req2).toJson());
                });
            });
            return;
        default:
            qDebug() << "All tests completed.";
            socket.disconnectFromHost();
            return;
        }
        socket.write(QJsonDocument(request).toJson());
    }

private:
    QTcpSocket socket;
    int currentTest = 0;
};

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    TestClient client;
    client.start();
    return app.exec();
}

#include "client.moc"
