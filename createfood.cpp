#include "createfood.h"
#include "ui_createfood.h"

CreateFood::CreateFood(RestaurantF * restaurant,QWidget *parent): QWidget(parent), ui(new Ui::CreateFood),restaurant(restaurant)
{
    ui->setupUi(this);
}

CreateFood::~CreateFood()
{
    delete ui;
}

void CreateFood::on_pushButtonOK_clicked()
{
    QString nameF = ui->nameLine->text().trimmed();
    QString typeF = ui->typeLine->text().trimmed();
    QString priceF = ui->priceLine->text().trimmed();
    QString ingredientF = ui->ingredientLine->text().trimmed();

    if (nameF.isEmpty() || typeF.isEmpty() || priceF.isEmpty() || ingredientF.isEmpty())
    {
        QMessageBox::warning(this, "خطا", "لطفاً همه‌ی فیلدها را پر کنید");
        return;
    }

    // بخش برای ذخیره سازی و ... نیازه
    this->hide();
    restaurant->show();
}


void CreateFood::on_pushButtonBack_clicked()
{
    this->hide();
    restaurant->show();
}

