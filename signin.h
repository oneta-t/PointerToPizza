#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include "mainwindow.h"
class MainWindow;

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
};

#endif // SIGNIN_H
