#ifndef RESTAURANTF_H
#define RESTAURANTF_H

#include <QWidget>
#include <QList>
#include <QTime>
#include "menuf.h"

namespace Ui {
class RestaurantF;
}

class RestaurantF : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantF(QWidget *parent = nullptr);
    RestaurantF(QString name,QString location ,QString start,QString end );//شاید باید منو هم باشه اینجا
    ~RestaurantF();

private:
    Ui::RestaurantF *ui;
    static int NextIdR;
    int IdR;
    QString Name;
    QString Location;
    QString StartTime;
    QString EndTime;
    MenuF menuF;
    //اینجا حتی میشه برای اینکه مثلا چه رئزهای هفته ای هستند هم چیز میز گذاشت
    //سفارشات
};

#endif // RESTAURANTF_H
