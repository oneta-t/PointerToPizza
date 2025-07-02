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

class SignIn : public QWidget
{
    Q_OBJECT

public:
    explicit SignIn(MainWindow* mainW, QWidget *parent = nullptr);
    ~SignIn();

private slots:
    void on_signInButto_clicked();

private:
    Ui::SignIn* ui;
    MainWindow* mainW;
    Customer* customerP;
    RestaurantManager* restaurantM;
};

#endif // SIGNIN_H
