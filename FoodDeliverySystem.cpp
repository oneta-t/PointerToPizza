#include "FoodDeliverySystem.h"
#include "customer.h"
#include "restaurantmanager.h"
#include <QRandomGenerator>

FoodDeliverySystem* FoodDeliverySystem::instance = nullptr;

FoodDeliverySystem* FoodDeliverySystem::getInstance()
{
    if (!instance) {
        instance = new FoodDeliverySystem();
        // اضافه کردن کاربران و رستوران نمونه
        instance->users.append(new Customer("User1", "", "pass1", "user1", "111", "customer"));
        instance->users.append(new RestaurantManager("Manager1", "", "pass2", "manager1", "222", "manager"));
        instance->restaurants.append(new Restaurant("Pizza Hut", "Tehran"));
        instance->deliveryPeople.append(new DeliveryPerson(1, "Ali", "available"));
    }
    return instance;
}

FoodDeliverySystem::FoodDeliverySystem(QObject *parent)
    : QObject(parent), nextOrderId(1)
{
    timer = new QTimer(this); //  تنظیم تایمر
    connect(timer, &QTimer::timeout, this, &FoodDeliverySystem::generateOrder);
    timer->start(5000);
}

FoodDeliverySystem::~FoodDeliverySystem()
{
    qDeleteAll(orders);
    qDeleteAll(users);
    qDeleteAll(restaurants);
    qDeleteAll(deliveryPeople);
    delete timer;
    instance = nullptr;
}

void FoodDeliverySystem::generateOrder()
{
    if (QRandomGenerator::global()->bounded(2) == 0 && nextOrderId <= 10) {
        Order* order = new Order(nextOrderId, nullptr, nullptr, QStringList() << QString("سفارش %1").arg(nextOrderId), "در حال پردازش", nullptr);
        orders.append(order); //  اضافه کردن سفارش
        nextOrderId++;
    }
}

void FoodDeliverySystem::removeUser(User* user)
{
    users.removeOne(user);
    delete user; //  حذف کاربر
}
