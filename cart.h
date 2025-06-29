#ifndef CART_H
#define CART_H

#include <QWidget>
#include "QList"
#include "fooditeam.h"

namespace Ui {
class Cart;
}

class Cart : public QWidget
{
    Q_OBJECT

public:
    explicit Cart(QWidget *parent = nullptr);
    Cart (float totalPrice);
    ~Cart();
    //تابع برای محاسبه قیمت
    void calculateTotalPrice();

private:
    Ui::Cart *ui;
    QList <FoodIteam*> Items;
    float TotalPrice;
};

#endif // CART_H
