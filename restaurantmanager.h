#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include <QWidget>
#include <QList>
#include "user.h"
#include "restaurantf.h"
#include "restaurantregistration.h"
class RestaurantRegistration;

namespace Ui {
class RestaurantManager;
}

class RestaurantManager : public QWidget ,public User
{
    Q_OBJECT

public:
    explicit RestaurantManager(QWidget *parent = nullptr);
    RestaurantManager(QString name,QString family,QString passw,QString username,QString phone,QString role);
    int getId() const;
    ~RestaurantManager();

private slots:
    void on_AddRestaurant_clicked();

private:
    Ui::RestaurantManager *ui;
    static int NextIdRM;
    int IdRM;
    QList<RestaurantF*> restaurants;
    RestaurantRegistration * Registration;

};

#endif // RESTAURANTMANAGER_H
