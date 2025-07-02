#include "signin.h"
#include "ui_signin.h"

SignIn::SignIn(MainWindow* mainW,QWidget *parent): QWidget(parent), ui(new Ui::SignIn),mainW(mainW)
{
    ui->setupUi(this);
    this->restaurantM = new RestaurantManager;
    this->customerP = new Customer;
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_signInButto_clicked()
{
    QString username = ui->lineEdit_username->text().trimmed();
    QString password1 = ui->lineEdit_pass->text().trimmed();

    UserRepository userRepo;
    int userId;
    QString role;

    if (userRepo.validateLogin(username, password, userId, role))
    {
        this->hide();

        if (role == "مشتری")
        {
            // ایجاد و نمایش صفحه مشتری
            this->customerP->show();
        }
        else if (role == "مدیر رستوران")
        {
            // ایجاد و نمایش صفحه مدیر رستوران
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

