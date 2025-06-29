#include "fooditeam.h"
#include "ui_fooditeam.h"

FoodIteam::FoodIteam(QWidget *parent): QWidget(parent), ui(new Ui::FoodIteam)
{
    ui->setupUi(this);
}

FoodIteam::~FoodIteam()
{
    delete ui;
}

int FoodIteam::NextIdF = 0;

FoodIteam::FoodIteam(QString foodName,QString type,float price)
{
    IdF=NextIdF++;
    FoodName=foodName;
    Price=price;
    Type=type;
}

float FoodIteam::getPrice() const { return Price; } // تابع getter برای دسترسی به Price
