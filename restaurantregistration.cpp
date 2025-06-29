#include "restaurantregistration.h"
#include "ui_restaurantregistration.h"

RestaurantRegistration::RestaurantRegistration(QWidget *parent): QWidget(parent), ui(new Ui::RestaurantRegistration)
{
    ui->setupUi(this);
}

RestaurantRegistration::~RestaurantRegistration()
{
    delete ui;
}

void RestaurantRegistration::on_pushButtonOK_clicked()
{
    QString nameR = ui->name->text().trimmed();
    QString address =ui->address->text().trimmed();
    QString startT =ui->start->text().trimmed();
    QString endT =ui->end->text().trimmed();

    if (nameR.isEmpty() || address.isEmpty() || startT.isEmpty() || endT.isEmpty())
    {
        QMessageBox::warning(this, "خطا", "لطفاً همه‌ی فیلدها را پر کنید");
        return;
    }
    //ایجاد شئی برای رستوران جدید
    RestaurantF * newRestaurant= new RestaurantF (name,address,startT,endT);
    //احتمالا اینجا باید ذخیره سازی کنیم
}

