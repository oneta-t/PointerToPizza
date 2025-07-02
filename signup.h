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

class SignUP : public QWidget
{
    Q_OBJECT

public:
    explicit SignUP(MainWindow* mainW, QWidget *parent = nullptr);
    ~SignUP();

private slots:
    void on_pushButtoYes_clicked();

private:
    Ui::SignUP *ui;
    MainWindow *mainW;
};

#endif // SIGNUP_H
