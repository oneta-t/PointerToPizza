#ifndef DELIVERYPERSON_H
#define DELIVERYPERSON_H

#include <QString>
#include <QList>
#include "order.h"

class DeliveryPerson
{
public:
    DeliveryPerson(int id, QString name, QString status);
    ~DeliveryPerson();

    int getId() const { return id; }
    QString getName() const { return name; }
    QString getStatus() const { return status; }
    QList<Order*> getAssignedOrders() const { return assignedOrders; }

private:
    int id;
    QString name;
    QString status;
    QList<Order*> assignedOrders;
};

#endif // DELIVERYPERSON_H
