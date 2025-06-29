#include "restaurantf.h"
#include "ui_restaurantf.h"

RestaurantF::RestaurantF(QWidget *parent): QWidget(parent), ui(new Ui::RestaurantF)
{
    ui->setupUi(this);
}

RestaurantF::~RestaurantF()
{
    delete ui;
}

int RestaurantF::NextIdR=0;

RestaurantF::RestaurantF(QString name,QString location,QString start,QString end)
{
    IdR=NextIdR++;
    Name=name;
    Location=location;
    StartTime=start;
    EndTime=end;
}
