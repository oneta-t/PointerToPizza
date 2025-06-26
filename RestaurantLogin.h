#ifndef RESTAURANTLOGIN_H
#define RESTAURANTLOGIN_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class RestaurantLogin;
}

class RestaurantLogin : public QWidget {
    Q_OBJECT
public:
    explicit RestaurantLogin(QWidget *parent = nullptr); // سازنده
    ~RestaurantLogin(); // نابودکننده

signals:
    void loginSuccess(int restaurantId); // سیگنال موفقیت

private slots:
    void handleLogin(); // مدیریت ورود

private:
    Ui::RestaurantLogin *ui; // رابط کاربری
    QSqlDatabase db; // دیتابیس
};

#endif // RESTAURANTLOGIN_H
