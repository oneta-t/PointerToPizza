#include "customer.h"
#include "ui_customer.h"

Customer::Customer(QWidget *parent): QWidget(parent), ui(new Ui::Customer)
{
    ui->setupUi(this);
}

int Customer::NextIdC=0;

Customer::Customer(QString name,QString family,QString passw,QString username,QString phone,QString role):User(name,family,passw,username,phone,role)
{
    IdC=NextIdC++;
}

Customer::~Customer()
{
    delete ui;
}
