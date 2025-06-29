#include "cart.h"
#include "ui_cart.h"

Cart::Cart(QWidget *parent): QWidget(parent), ui(new Ui::Cart)
{
    ui->setupUi(this);
}

Cart::~Cart()
{
    delete ui;
}

Cart::Cart (float totalPrice)
{
    TotalPrice= totalPrice;
}

void Cart::calculateTotalPrice() {
    TotalPrice = 0.0;
    // مقدار اولیه را صفر کنید
    for (FoodIteam* item : Items)
    {
        // قیمت هر آیتم را به TotalPrice اضافه کنید
        TotalPrice += item->getPrice();
    }
}
