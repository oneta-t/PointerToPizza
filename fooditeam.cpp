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

FoodIteam::FoodIteam(QString foodName, QString ingredients, QString type, float price)
{
    IdF=NextIdF++;
    FoodName=foodName;
    Ingredients=ingredients;
    Price=price;
    Type=type;
}

QString FoodIteam::getFoodName() const { return FoodName; }

QString FoodIteam::getType() const { return Type; }

float FoodIteam::getPrice() const { return Price; }

QString FoodIteam::getIngredients()const { return Ingredients;}
