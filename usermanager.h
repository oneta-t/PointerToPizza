#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QWidget>
#include <QList>
#include "user.h"
#include "customer.h"
// for restaurantmanager
class UserManager
{
public:
    static UserManager& instance();
    void addCustomer(Customer* customer);
    const QList<Customer*>& getCustomers() const;

private:
    UserManager() = default;
    QList<Customer*> customers;
};

#endif // USERMANAGER_H
