#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include <QWidget>
#include <QList>
#include "user.h"
#include "restaurant.h"

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

private:
    Ui::RestaurantManager *ui;
    static int NextIdRM;
    int IDRM;
    QList<Restauran> restaurants;

};

#endif // RESTAURANTMANAGER_H
