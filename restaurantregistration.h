#ifndef RESTAURANTREGISTRATION_H
#define RESTAURANTREGISTRATION_H

#include <QWidget>
#include "restaurantf.h"

namespace Ui {
class RestaurantRegistration;
}

class RestaurantRegistration : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantRegistration(QWidget *parent = nullptr);
    ~RestaurantRegistration();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::RestaurantRegistration *ui;
};

#endif // RESTAURANTREGISTRATION_H
