#ifndef FOODDELIVERYSYSTEM_H
#define FOODDELIVERYSYSTEM_H

#include <QObject>
#include <QTimer>
#include <QList>
#include "user.h"
#include "customer.h"
#include "restaurantmanager.h"
#include "order.h"
#include "deliveryperson.h"
#include "restaurant.h"


class FoodDeliverySystem : public QObject
{
    Q_OBJECT
public:
    static FoodDeliverySystem* getInstance();
    ~FoodDeliverySystem();

    QList<User*> getUsers() const { return users; }
    QList<Order*> getOrders() const { return orders; }
    QList<Restaurant*> getRestaurants() const { return restaurants; }
    void removeUser(User* user);

signals:
    void newOrderReceived(User* owner, const Order* order); //  سیگنال سفارش جدید

private slots:
    void generateOrder(); //  تولید سفارش

private:
    FoodDeliverySystem(QObject *parent = nullptr);
    static FoodDeliverySystem* instance;
    QTimer* timer;
    int nextOrderId;
    QList<Order*> orders;
    QList<User*> users;
    QList<Restaurant*> restaurants;
    QList<DeliveryPerson*> deliveryPeople;
};

#endif // FOODDELIVERYSYSTEM_H
