#include "userinformationpage.h"
#include "ui_userinformationpage.h"

UserInformationPage::UserInformationPage(Customer *CustomerPage,QWidget *parent): QWidget(parent), ui(new Ui::UserInformationPage),CustomerPage(CustomerPage)
{
    ui->setupUi(this);
}

UserInformationPage::~UserInformationPage()
{
    delete ui;
}

void UserInformationPage::on_pushButton_clicked()
{
    this->hide();
    CustomerPage->show();
}

