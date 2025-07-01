#include "order.h"

Order::Order(int id, Customer* customer, RestaurantManager* restaurant, const QStringList& items, Order::Status status, DeliveryPerson* deliveryPerson)
    : id(id), customer(customer), restaurant(restaurant), items(items), status(status), deliveryPerson(deliveryPerson), statusHistory(new OrderStatusHistory)
{
    statusHistory->addStatusChange(getStatusText()); // ثبت وضعیت اولیه
}

Order::~Order()
{
    delete deliveryPerson;
    delete statusHistory; //  پاک‌سازی تاریخچه
}

void Order::setStatus(Status newStatus)
{
    status = newStatus;
    statusHistory->addStatusChange(getStatusText()); //  افزودن به تاریخچه
}

QString Order::getStatusText() const
{
    switch (status) {
    case Preparing: return "آماده‌سازی";
    case Shipping: return "ارسال";
    case Delivered: return "تحویل";
    default: return "در حال پردازش";
    }
}
