#ifndef RESTAURANTF_H
#define RESTAURANTF_H

#include <QWidget>
#include <QList>
#include <QTime>
#include "menuf.h"
#include "createfood.h"

class CreateFood ;

namespace Ui {
class RestaurantF;
}

class RestaurantF : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantF(int id, int ownerId, QString name, QString address, QString startTime, QString endTime, QWidget *parent = nullptr);
    ~RestaurantF();
    int getIdR() const ;
    QString getName() const ;
    QString getLocation() const ;
    QString getStartTime() const ;
    QString getEndTime() const ;
    MenuF* getMenuF() const;
    int getOwnerId() const;

private slots:
    void on_addMenu_clicked();

private:
    Ui::RestaurantF *ui;
    CreateFood *createF;
    int IdR;
    int ownerId;
    QString Name;
    QString Location;
    QString StartTime;
    QString EndTime;
    MenuF *menuF;
    //اینجا حتی میشه برای اینکه مثلا چه رئزهای هفته ای هستند هم چیز میز گذاشت
    //سفارشات
};

#endif // RESTAURANTF_H
