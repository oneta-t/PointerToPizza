#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QWidget>
#include <QList>
#include <QTime>
#include "menu.h"

namespace Ui {
class Restaurant;
}

class Restaurant : public QWidget
{
    Q_OBJECT

public:
    explicit Restaurant(QWidget *parent = nullptr);
    Restaurant(QString name,QString location);//شاید باید منو هم باشه اینجا
    ~Restaurant();

private:
    Ui::Restauran *ui;
    static int NextIdR;
    int IdR;
    QString Name;
    QString Location;
    QString StartTime;
    QString EndTime;
    Menu menuF;
    //اینجا حتی میشه برای اینکه مثلا چه رئزهای هفته ای هستند هم چیز میز گذاشت
    //سفارشات

};

#endif // RESTAURANT_H
