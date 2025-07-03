#include "fooditeam.h"

FoodIteam::FoodIteam(int itemId, const QString& foodName, const QString& ingredients,
                     const QString& type, float price, QWidget *parent)
    : QWidget(parent), itemId(itemId), foodName(foodName), ingredients(ingredients),
    type(type), price(price)
{
    setupUi();
}

int FoodIteam::getItemId() const { return itemId; }

QString FoodIteam::getFoodName() const { return foodName; }

QString FoodIteam::getIngredients() const { return ingredients; }

QString FoodIteam::getType() const { return type; }

float FoodIteam::getPrice() const { return price; }

void FoodIteam::setupUi()
{
    QLabel* nameLabel = new QLabel("نام غذا: " + foodName, this);
    QLabel* ingredientsLabel = new QLabel("مواد اولیه: " + ingredients, this);
    QLabel* typeLabel = new QLabel("نوع: " + type, this);
    QLabel* priceLabel = new QLabel(QString("قیمت: %1").arg(price), this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(ingredientsLabel);
    layout->addWidget(typeLabel);
    layout->addWidget(priceLabel);
    layout->addStretch();

    setLayout(layout);
}
