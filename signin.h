#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include "mainwindow.h"
#include "RestaurantManager.h"
#include "userrepository.h"
#include "customer.h"

class MainWindow;
class RestaurantManager;

namespace Ui {
class SignIn;
}

class SignIn : public QWidget
{
    Q_OBJECT

public:
    explicit SignIn(MainWindow* mainW,QWidget *parent = nullptr);
    ~SignIn();

private slots:
    void on_signInButto_clicked();

private:
    Ui::SignIn *ui;
    MainWindow *mainW;
    RestaurantManager * restaurantM;
    Customer *customerP;
};

#endif // SIGNIN_H
