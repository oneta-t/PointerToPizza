#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>
#include "user.h"
#include "cart.h"
#include "userinformationpage.h"
class UserInformationPage;

namespace Ui {
class Customer;
}

class Customer : public QWidget, public User
{
    Q_OBJECT

public:
    explicit Customer(QWidget *parent = nullptr);
    Customer(QString name,QString family,QString passw,QString username,QString phone,QString role);
    int getId() const;
    ~Customer();

private slots:
    void on_UserInfButton_clicked();

private:
    Ui::Customer *ui;
    UserInformationPage *InfPage;
    static int NextIdC;
    int IdC;
    Cart *cart;
};

#endif // CUSTOMER_H
