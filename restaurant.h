#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QWidget>
#include <QList>
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
    Menu menuF;
    //سفارشات

};

#endif // RESTAURANT_H
