#include "signin.h"
#include "ui_signin.h"

SignIn::SignIn(MainWindow* mainW,QWidget *parent): QWidget(parent), ui(new Ui::SignIn),mainW(mainW)
{
    ui->setupUi(this);
    this->restaurantM = new RestaurantManager;
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_signInButto_clicked()
{
    this->hide();
    QString username = ui->lineEdit_username->text().trimmed();
    QString password1 = ui->lineEdit_pass->text().trimmed();// خطررررررر
    this->restaurantM->show();   // اینجا ما باید در لیست بگردیم و چک کنیم و صفحه ی هر کس را بیاوریم برایش
}

