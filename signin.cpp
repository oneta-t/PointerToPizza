#include "SignIn.h"
#include "ui_SignIn.h"
#include <QMessageBox>
#include "UserRepository.h"

// سازنده با اشاره‌گر به MainWindow
SignIn::SignIn(MainWindow* mainW, QWidget *parent)
    : QWidget(parent), ui(new Ui::SignIn), mainW(mainW), customerP(nullptr), restaurantM(nullptr)
{
    ui->setupUi(this);
}

// دestructor
SignIn::~SignIn()
{
    delete ui;
    delete customerP;
    delete restaurantM;
}

// بررسی ورود کاربر
void SignIn::on_signInButto_clicked()
{
    QString username = ui->lineEdit_username->text().trimmed();
    QString password = ui->lineEdit_pass->text().trimmed();

    UserRepository userRepo;
    int userId;
    QString role, name, family, phone, passwordOut;

    // اعتبارسنجی ورود
    if (userRepo.validateLogin(username, password, userId, role, name, family, phone, passwordOut))
    {
        this->hide();

        if (role == "مشتری")
        {
            // ایجاد شیء Customer با اطلاعات کامل
            if (!customerP)
                customerP = new Customer(userId, name, family, passwordOut, username, phone, role, this);
            customerP->show();
        }
        else if (role == "مدیر رستوران")
        {
            // ایجاد شیء RestaurantManager با اطلاعات کامل
            if (!restaurantM)
                restaurantM = new RestaurantManager(userId, name, family, passwordOut, username, phone, role, this);
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
