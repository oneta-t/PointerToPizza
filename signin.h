#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include "MainWindow.h"
#include "Customer.h"
#include "RestaurantManager.h"
class MainWindow;

namespace Ui {
class SignIn;
}

// کلاس فرم ورود کاربر
class SignIn : public QWidget
{
    Q_OBJECT

public:
    // سازنده با اشاره‌گر به MainWindow
    explicit SignIn(MainWindow* mainW, QWidget *parent = nullptr);
    // دestructor
    ~SignIn();

private slots:
    // بررسی ورود کاربر
    void on_signInButto_clicked();

private:
    Ui::SignIn* ui; // رابط کاربری فرم
    MainWindow* mainW; // اشاره‌گر به پنجره اصلی
    Customer* customerP; // اشاره‌گر به صفحه مشتری
    RestaurantManager* restaurantM; // اشاره‌گر به صفحه مدیر رستوران
};

#endif // SIGNIN_H
