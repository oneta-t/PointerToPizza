#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include <QWidget>
#include <QList>
#include "user.h"
#include "restaurantf.h"
#include "restaurantregistration.h"
#include "restaurantmodel.h"

    class RestaurantRegistration;

namespace Ui {
class RestaurantManager;
}

// کلاس RestaurantManager برای مدیریت صفحه مدیر رستوران
class RestaurantManager : public QWidget, public User
{
    Q_OBJECT

public:
    // سازنده با userId برای شناسایی مدیر
    explicit RestaurantManager(int userId, QWidget *parent = nullptr);
    ~RestaurantManager();

    void loadRestaurants();

    int getUserId() const { return userId; }

private slots:
    // اسلات برای دکمه افزودن رستوران
    void on_AddRestaurant_clicked();

private:
    Ui::RestaurantManager *ui;
    RestaurantRegistration *registration;
    RestaurantModel *restaurantModel;
    int userId;
    QList <RestaurantF*>restaurants;
};

#endif // RESTAURANTMANAGER_H
