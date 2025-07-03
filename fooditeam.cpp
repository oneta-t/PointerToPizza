#include "fooditeam.h"
#include "ui_fooditeam.h"

FoodIteam::~FoodIteam()
{
    delete ui;
}

FoodIteam::FoodIteam(int id, int restaurantId, QString foodName, QString ingredients, QString type, float price, QWidget *parent)
    : QWidget(parent), ui(new Ui::FoodIteam), id(id), restaurantId(restaurantId), foodName(foodName), ingredients(ingredients), type(type), price(price)
{
    ui->setupUi(this);
}

QString FoodIteam::getFoodName() const { return FoodName; }

QString FoodIteam::getType() const { return Type; }

float FoodIteam::getPrice() const { return Price; }

QString FoodIteam::getIngredients()const { return Ingredients;}
