#include "signin.h"
#include "ui_signin.h"

SignIn::SignIn(MainWindow* mainW,QWidget *parent): QWidget(parent), ui(new Ui::SignIn),mainW(mainW)
{
    ui->setupUi(this);
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_signInButto_clicked()
{
    this->hide();
    mainW->show();   //we have to used user page or ... for this
}

