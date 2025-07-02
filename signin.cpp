#include "SignIn.h"
#include "ui_SignIn.h"
#include <QMessageBox>
#include "UserRepository.h"

SignIn::SignIn(MainWindow* mainW, QWidget *parent)
    : QWidget(parent), ui(new Ui::SignIn), mainW(mainW), customerP(nullptr), restaurantM(nullptr)
{
    ui->setupUi(this);
}

SignIn::~SignIn()
{
    delete ui;
    delete customerP;
    delete restaurantM;
}

void SignIn::on_signInButto_clicked()
{
    QString username = ui->lineEdit_username->text().trimmed();
    QString password = ui->lineEdit_pass->text().trimmed();

    UserRepository userRepo;
    int userId;
    QString role;

    if (userRepo.validateLogin(username, password, userId, role))
    {
        this->hide();

        if (role == "مشتری")
        {
            if (!customerP)
                customerP = new Customer(userId, this);
            customerP->show();
        }
        else if (role == "مدیر رستوران")
        {
            if (!restaurantM)
                restaurantM = new RestaurantManager(userId, this);
            restaurantM->show();
        }
        else
        {
            QMessageBox::warning(this, "خطا", "نقش کاربر نامعتبر است.");
            this->show();
        }
    }
    else
    {
        QMessageBox::warning(this, "خطا", "نام کاربری یا رمز عبور اشتباه است.");
    }
}
