#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QJsonObject>
#include "userrepository.h"
#include "database.h"

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    // شروع به کار سرور روی پورت مشخص
    bool startServer(quint16 port);

protected:
    // مدیریت اتصالات ورودی
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    // خواندن داده های ارسالی از کلاینت
    void readClientData();

    // مدیریت قطع ارتباط کلاینت
    void clientDisconnected();

private:
    // توابع مدیریت درخواست های  مختلف
    void handleRegister(const QJsonObject& json, QTcpSocket* client);
    void handleLogin(const QJsonObject& json, QTcpSocket* client);
    void handleGetRestaurants(QTcpSocket* client);
    void handleGetMenu(const QJsonObject& json, QTcpSocket* client);
    void handleOrder(const QJsonObject& json, QTcpSocket* client);
    void handleGetMyOrders(QTcpSocket* client);
    void handleChangeOrderStatus(const QJsonObject& json, QTcpSocket* client);
    void handleGetOrdersForRestaurant(QTcpSocket* client);
    void handleAddMenuItem(const QJsonObject& json, QTcpSocket* client);
    void notifyRestaurant(int restaurantId, const QString& message);

    QMap<qintptr, QTcpSocket*> clients; // ارتباط دادن شناسه سوکت به آبجکت سوکت کلاینت
    QMap<qintptr, int> clientUserIds; // ارتباط دادن شناسه سوکت به شناسه کاربر
    UserRepository userRepo; // برای دسترسی به داده های کاربران
};

#endif // SERVER_H
