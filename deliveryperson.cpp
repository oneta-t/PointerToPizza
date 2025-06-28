#include "deliveryperson.h"

DeliveryPerson::DeliveryPerson(int id, QString name, QString status)
    : id(id), name(name), status(status)
{
}

DeliveryPerson::~DeliveryPerson()
{
    qDeleteAll(assignedOrders);
}
