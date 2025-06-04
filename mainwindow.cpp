#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->signUp=new SignUP(this);
    this->signin=new SignIn (this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    this->signUp->show();
}


void MainWindow::on_pushButton_clicked()
{
    this->hide();
    this->signin->show();
}

