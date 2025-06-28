#include "order.h"

Order::Order(int id, Customer* customer, RestaurantManager* restaurant, const QStringList& items, const QString& status, DeliveryPerson* deliveryPerson)
    : id(id), customer(customer), restaurant(restaurant), items(items), status(status), deliveryPerson(deliveryPerson)
{
}

Order::~Order()
{
    delete deliveryPerson;
}
