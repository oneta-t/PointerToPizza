#include "createfood.h"
#include "ui_createfood.h"
#include <QMessageBox>

CreateFood::CreateFood(RestaurantF *restaurant, QWidget *parent)
    : QWidget(parent), ui(new Ui::CreateFood), restaurant(restaurant)
{
    ui->setupUi(this);
}

CreateFood::~CreateFood()
{
    delete ui;
}

// مدیریت کلیک روی دکمه تأیید (OK)
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

    bool ok;
    float price = priceF.toFloat(&ok);
    if (!ok || price <= 0) {
        QMessageBox::warning(this, "خطا", "قیمت باید یک عدد مثبت باشد");
        return;
    }

    // ذخیره غذا در دیتابیس
    if (menuRepo.addMenuItem(restaurant->getId(), nameF, price, typeF))
    {
        QMessageBox::information(this, "موفقیت", "غذا با موفقیت به منو اضافه شد!");
        this->hide();
        restaurant->show();
        // لود مجدد منو
        if (restaurant->getMenuF()) {
            restaurant->getMenuF()->loadMenu();
        }
    }
    else
    {
        QMessageBox::warning(this, "خطا", "اضافه کردن غذا به منو ناموفق بود.");
    }
}

// مدیریت کلیک روی دکمه بازگشت (Back)
void CreateFood::on_pushButtonBack_clicked()
{
    this->hide();
    restaurant->show();
}
