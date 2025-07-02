#ifndef USERINFORMATIONPAGE_H
#define USERINFORMATIONPAGE_H

#include <QWidget>
#include "customer.h"

class Customer;

namespace Ui {
class UserInformationPage;
}

class UserInformationPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserInformationPage(Customer *CustomerPage,QWidget *parent = nullptr);
    ~UserInformationPage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UserInformationPage *ui;
    Customer * CustomerPage;
};

#endif // USERINFORMATIONPAGE_H
