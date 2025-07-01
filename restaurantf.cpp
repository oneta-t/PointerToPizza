#include "restaurantf.h"
#include "ui_restaurantf.h"

RestaurantF::RestaurantF(QWidget *parent): QWidget(parent), ui(new Ui::RestaurantF)
{
    ui->setupUi(this);
    this->createF = new CreateFood(this);
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

int RestaurantF::getIdR() const { return IdR; }

QString RestaurantF::getName() const { return Name; }

QString RestaurantF::getLocation() const { return Location; }

QString RestaurantF::getStartTime() const { return StartTime; }

QString RestaurantF::getEndTime() const { return EndTime; }

MenuF* RestaurantF::getMenuF() const { return menuF; }

void RestaurantF::on_addMenu_clicked()
{
    this->hide();
    this->createF->show();
}

