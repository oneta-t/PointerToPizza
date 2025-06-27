#ifndef RESTAURANTLOGIN_H
#define RESTAURANTLOGIN_H

#include <QWidget>
#include "user.h"

namespace Ui {
class RestaurantLogin;
}

class RestaurantLogin : public User {
    Q_OBJECT
public:
    explicit RestaurantLogin(QWidget *parent = nullptr); // سازنده
    ~RestaurantLogin() ; // نابودگر

signals:
    void loginSuccess(int restaurantId); // سیگنال موفقیت لاگین

private slots:
    void handleLogin(); // مدیریت رویداد ورود

private:
    Ui::RestaurantLogin *ui; // رابط کاربری
    // آرایه ثابت برای کاربران رستوران‌دار
    static const struct {
        QString username;
        QString password;
        int id;
    } restaurantUsers[];
    static const int userCount;
};

#endif // RESTAURANTLOGIN_H
