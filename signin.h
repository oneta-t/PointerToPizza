#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include "mainwindow.h"
#include "restaurantmanager.h"
#include "userrepository.h"
#include "customer.h"

class MainWindow;

namespace Ui {
class SignIn;
}

// کلاس SignIn برای مدیریت صفحه ورود
class SignIn : public QWidget
{
    Q_OBJECT

public:
    explicit SignIn(MainWindow* mainW, QWidget *parent = nullptr);
    ~SignIn();

private slots:
    // اسلات برای دکمه ورود
    void on_signInButto_clicked();

private:
    Ui::SignIn *ui;
    MainWindow *mainW;
    RestaurantManager *restaurantM;
    Customer *customerP;
};

#endif // SIGNIN_H
