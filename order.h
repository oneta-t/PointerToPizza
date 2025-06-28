#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QStringList>

class Customer;
class RestaurantManager;
class DeliveryPerson;

class Order //  کلاس برای تعریف سفارش
{
public:
    Order(int id, Customer* customer, RestaurantManager* restaurant, const QStringList& items, const QString& status, DeliveryPerson* deliveryPerson);
    ~Order();

    int getId() const { return id; }
    QString getStatus() const { return status; }

private:
    int id;
    Customer* customer;
    RestaurantManager* restaurant;
    QStringList items;
    QString status;
    DeliveryPerson* deliveryPerson;
};

#endif // ORDER_H
