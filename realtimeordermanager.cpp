#include "realtimeordermanager.h"
#include <QRandomGenerator>
#include <QDebug>

RealTimeOrderManager::RealTimeOrderManager(RestaurantManager* manager, QObject *parent)
    : QObject(parent), manager(manager), nextOrderId(1)
{
    timer = new QTimer(this); // تنظیم تایمر
    connect(timer, &QTimer::timeout, this, &RealTimeOrderManager::generateOrder);
    timer->start(5000); // 5 ثانیه
}

RealTimeOrderManager::~RealTimeOrderManager()
{
    delete timer; //  پاک‌سازی تایمر
}

void RealTimeOrderManager::generateOrder()
{
    if (QRandomGenerator::global()->bounded(2) == 0 && nextOrderId <= 10) { // 50% شانس
        QStringList items = QStringList() << QString("سفارش بلادرنگ %1").arg(nextOrderId);
        Order* order = new Order(nextOrderId, nullptr, nullptr, items, Order::Processing, nullptr);
        emit newOrderGenerated(order); // ارسال سیگنال
        qDebug() << "سفارش بلادرنگ تولید شد:" << nextOrderId;
        nextOrderId++;
    }
}
