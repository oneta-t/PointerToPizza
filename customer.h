#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>
#include <QList>
#include "user.h"
#include "cart.h"
#include "userinformationpage.h"
#include "menuf.h"
#include "order.h"

class UserInformationPage;

namespace Ui {
class Customer;
}

// کلاس Customer برای مدیریت صفحه مشتری
class Customer : public QWidget, public User
{
    Q_OBJECT

public:
    explicit Customer(int userId, QWidget *parent = nullptr);
    ~Customer();
    void loadRestaurants(); // لود رستوران‌ها
    void loadMenu(int restaurantId); // لود منوی رستوران

private slots:
    // اسلات برای دکمه اطلاعات کاربر
    void on_UserInfButton_clicked();

private:
    Ui::Customer *ui;
    UserInformationPage *InfPage;
    Cart *cart;
    QList <order*>ordersHistory;
    int userId;
};

#endif // CUSTOMER_H
