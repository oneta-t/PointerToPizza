#include "restaurantregistration.h"
#include "ui_restaurantregistration.h"

RestaurantRegistration::RestaurantRegistration(RestaurantManager * RManager,QWidget *parent): QWidget(parent), ui(new Ui::RestaurantRegistration),RManager(RManager)
{
    ui->setupUi(this);
}

RestaurantRegistration::~RestaurantRegistration()
{
    delete ui;
}

void RestaurantRegistration::on_pushButtonOK_clicked()
{
    this->hide();
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
    RestaurantF * newRestaurant= new RestaurantF (nameR,address,startT,endT);
    //احتمالا اینجا باید ذخیره سازی کنیم
    RManager->show();

}


void RestaurantRegistration::on_pushButtonBack_clicked()
{
    this ->hide();
    RManager->show();
}

