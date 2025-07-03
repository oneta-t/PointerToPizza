#include "signin.h"
#include "ui_signin.h"
#include "userrepository.h"
#include <QMessageBox>

// سازنده کلاس SignIn
SignIn::SignIn(MainWindow* mainW, QWidget *parent) : QWidget(parent), ui(new Ui::SignIn), mainW(mainW)
{
    // راه‌اندازی رابط کاربری
    ui->setupUi(this);
    this->restaurantM = nullptr;
    this->customerP = nullptr;
}

// دستراکتور برای آزادسازی منابع
SignIn::~SignIn()
{
    delete ui;
    delete restaurantM;
    delete customerP;
}

// مدیریت کلیک روی دکمه ورود
void SignIn::on_signInButto_clicked()
{
    // دریافت اطلاعات ورودی از فرم
    QString username = ui->lineEdit_username->text().trimmed();
    QString password = ui->lineEdit_pass->text().trimmed();

    UserRepository userRepo;
    int userId;
    QString role;

    // اعتبارسنجی ورود کاربر
    if (userRepo.validateLogin(username, password, userId, role))
    {
        // مخفی کردن صفحه ورود
        this->hide();
        if (role == "مشتری")
        {
            this->customerP = new Customer(userId, this);
            this->customerP->show();
        }
        else if (role == "مدیر رستوران")
        {
            this->restaurantM = new RestaurantManager(userId, this);
            this->restaurantM->show();
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
