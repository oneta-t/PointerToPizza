#ifndef CREATEFOOD_H
#define CREATEFOOD_H

#include <QWidget>
#include "restaurantf.h"
#include "menurepository.h"

    class RestaurantF;

namespace Ui {
class CreateFood;
}

class CreateFood : public QWidget
{
    Q_OBJECT

public:
    explicit CreateFood(RestaurantF *restaurant, QWidget *parent = nullptr);
    ~CreateFood();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonBack_clicked();

private:
    Ui::CreateFood *ui;
    RestaurantF *restaurant;
    MenuRepository menuRepo;
};

#endif // CREATEFOOD_H
