#ifndef RESTAURANTREGISTRATION_H
#define RESTAURANTREGISTRATION_H

#include <QWidget>

namespace Ui {
class RestaurantRegistration;
}

class RestaurantRegistration : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantRegistration(QWidget *parent = nullptr);
    ~RestaurantRegistration();

private:
    Ui::RestaurantRegistration *ui;
};

#endif // RESTAURANTREGISTRATION_H
