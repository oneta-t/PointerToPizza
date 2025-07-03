#include "customer.h"
#include "ui_customer.h"

Customer::Customer(QWidget *parent): QWidget(parent), ui(new Ui::Customer)
{
    ui->setupUi(this);
    this->InfPage=new UserInformationPage (this);
}

Customer::Customer(QString name,QString family,QString passw,QString username,QString phone,QString role):User(name,family,passw,username,phone,role)
{
    I
}

Customer::~Customer()
{
    delete ui;
}

void Customer::on_UserInfButton_clicked()
{
    this->hide();
    this->InfPage->show();
}

