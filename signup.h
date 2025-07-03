#ifndef SIGNUP_H
#define SIGNUP_H
#include <QWidget>
#include <QMessageBox>
#include "mainwindow.h"
#include "user.h"
#include "customer.h"
#include "restaurantmanager.h"
#include "userrepository.h"

class MainWindow;

namespace Ui {
class SignUP;
}

// کلاس SignUP برای مدیریت صفحه ثبت‌نام
class SignUP : public QWidget
{
    Q_OBJECT

public:
    // سازنده با اشاره‌گر به پنجره اصلی
    explicit SignUP(MainWindow* mainW, QWidget *parent = nullptr);
    // دستراکتور برای آزادسازی منابع
    ~SignUP();

private slots:
    // اسلات برای دکمه ثبت‌نام
    void on_pushButtoYes_clicked();

private:
    Ui::SignUP *ui; // رابط کاربری
    MainWindow *mainW; // اشاره‌گر به پنجره اصلی
};

#endif // SIGNUP_H
