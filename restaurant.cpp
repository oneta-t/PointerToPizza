#include "restaurant.h"
#include "ui_restaurant.h"

Restaurant::Restaurant(QWidget *parent): QWidget(parent), ui(new Ui::Restaurant)
{
    ui->setupUi(this);
}

Restaurant::~Restaurant()
{
    delete ui;
}

int Restaurant::NextIdR=0;

Restaurant::Restaurant(QString name,QString location)
{
    IdR=NextIdR++;
    Name=name;
    Location=locat
}
