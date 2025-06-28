#include "restaurantregistration.h"
#include "ui_restaurantregistration.h"

RestaurantRegistration::RestaurantRegistration(QWidget *parent): QWidget(parent), ui(new Ui::RestaurantRegistration)
{
    ui->setupUi(this);
}

RestaurantRegistration::~RestaurantRegistration()
{
    delete ui;
}
