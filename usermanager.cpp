#include "usermanager.h"

UserManager& UserManager::instance()
{
    static UserManager instance;
    return instance;
}

void UserManager::addCustomer(Customer* customer)
{
    customers.append(customer);
}

const QList<Customer*>& UserManager::getCustomers() const
{
    return customers;
}

// برای مدیر رستوران هم باید زد این بخشو
