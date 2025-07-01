#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include <QWidget>
#include "user.h"
#include <QList>
#include "restaurantf.h"
#include "restaurantregistration.h"
#include "restaurantmodel.h"
#include "realtimeordermanager.h"
#include "order.h"
//کتابخوانه های دیگه ای هم باید اضافه شود فعلا برای حل شدن کار بلادرنگ  اینارو فراخوان کردم

namespace Ui {
class RestaurantManager;
}

class RestaurantManager : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantManager(QWidget *parent = nullptr);
    RestaurantManager(QString name,QString family,QString passw,QString username,QString phone,QString role);
    int getId() const;
    ~RestaurantManager();
RestaurantModel* restaurantModel; // مدل رستوران‌ها
    QList<Order*> orders; // لیست سفارش‌ها

private slots:
    void on_AddRestaurant_clicked();
    void handleNewOrder(Order* order); // مدیریت سفارش جدید
    void on_UpdateStatus_clicked(); // تغییر وضعیت سفارش

private:
    Ui::RestaurantManager *ui;
    static int NextId;
    int ID;
QList<RestaurantF*> restaurants;
    RestaurantRegistration* Registration;
    RealTimeOrderManager* orderManager; // مدیر سفارش بلادرنگ
};

#endif // RESTAURANTMANAGER_H
