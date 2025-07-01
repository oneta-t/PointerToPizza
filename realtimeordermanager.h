#ifndef REALTIMEORDERMANAGER_H
#define REALTIMEORDERMANAGER_H

#include <QObject>
#include <QTimer>
#include <QList>
#include "order.h"
#include "restaurantf.h"
#include "restaurantmanager.h"

// مدیریت سفارش‌های بلادرنگ
class RealTimeOrderManager : public QObject
{
    Q_OBJECT

public:
    explicit RealTimeOrderManager(RestaurantManager* manager, QObject *parent = nullptr);
    ~RealTimeOrderManager();

signals:
    void newOrderGenerated(Order* order); // سیگنال برای سفارش جدید

private slots:
    void generateOrder(); // تولید سفارش به‌صورت بلادرنگ

private:
    RestaurantManager* manager; // اشاره‌گر به مدیر رستوران
    QTimer* timer; // تایمر برای شبیه‌سازی بلادرنگ
    int nextOrderId; // شناسه سفارش
};

#endif // REALTIMEORDERMANAGER_H
