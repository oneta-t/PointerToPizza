#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QStringList>
#include "orderstatushistory.h"

class Customer;
class RestaurantManager;
class DeliveryPerson;

class Order //  کلاس برای تعریف سفارش
{
public:
    enum Status { Processing, Preparing, Shipping, Delivered }; // وضعیت‌های سفارش

    Order(int id, Customer* customer, RestaurantManager* restaurant, const QStringList& items, Status status, DeliveryPerson* deliveryPerson);
    ~Order();

    int getId() const { return id; }
    Status getStatus() const { return status; }
    void setStatus(Status newStatus); // تغییر وضعیت
    QString getStatusText() const; // تبدیل وضعیت به متن
    OrderStatusHistory* getStatusHistory() const { return statusHistory; } // تاریخچه وضعیت

private:
    int id;
    Customer* customer;
    RestaurantManager* restaurant;
    QStringList items;
    Status status;
    DeliveryPerson* deliveryPerson;
    OrderStatusHistory* statusHistory; // تاریخچه وضعیت
};

#endif // ORDER_H
