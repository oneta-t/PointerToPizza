#include "signup.h"
#include "ui_signup.h"
#include "userrepository.h"
#include <QCryptographicHash>
#include <QSqlQuery>
#include <QSqlError>

// سازنده کلاس SignUP
SignUP::SignUP(MainWindow* mainW, QWidget *parent) : QWidget(parent), ui(new Ui::SignUP), mainW(mainW)
{
    // راه‌اندازی رابط کاربری
    ui->setupUi(this);
}

// دستراکتور برای آزادسازی منابع
SignUP::~SignUP()
{
    delete ui;
}

// مدیریت کلیک روی دکمه ثبت‌نام
void SignUP::on_pushButtoYes_clicked()
{
    // دریافت اطلاعات ورودی از فرم
    QString name = ui->lineEdit_name->text().trimmed();
    QString family = ui->lineEdit_family->text().trimmed();
    QString username = ui->lineEdit_usernem->text().trimmed();
    QString password1 = ui->lineEdit_pass->text().trimmed();
    QString password2 = ui->lineEdit_pass_2->text().trimmed();
    QString phone = ui->lineEdit_phon->text().trimmed();
    QString role = ui->comboBoxType->currentText();

    // بررسی پر بودن همه فیلدها
    if (name.isEmpty() || family.isEmpty() || username.isEmpty() || password1.isEmpty() || phone.isEmpty() || ui->comboBoxType->currentIndex() == 0)
    {
        QMessageBox::warning(this, "خطا", "لطفاً همه‌ی فیلدها را پر کنید");
        return;
    }

    // بررسی یکسان بودن رمز عبور و تکرار آن
    if (password1 != password2)
    {
        QMessageBox::warning(this, "خطا", "رمز و تکرار آن یکسان نیست. لطفاً دوباره امتحان کنید");
        return;
    }

    // بررسی وجود نام کاربری در دیتابیس
    UserRepository userRepo;
    if (userRepo.userExists(username))
    {
        QMessageBox::warning(this, "خطا", "نام کاربری قبلاً وجود دارد.");
        return;
    }

    // افزودن کاربر به دیتابیس با استفاده از UserRepository
    if (userRepo.addUser(username, password1, role))
    {
        // افزودن اطلاعات اضافی (نام، نام خانوادگی، شماره تلفن) به دیتابیس
        QSqlQuery query;
        query.prepare("UPDATE users SET name = :name, family = :family, phone = :phone WHERE username = :username");
        query.bindValue(":name", name);
        query.bindValue(":family", family);
        query.bindValue(":phone", phone);
        query.bindValue(":username", username);

        if (query.exec())
        {
            QMessageBox::information(this, "ثبت‌نام موفق", "ثبت‌نام با موفقیت انجام شد!");
            this->hide(); // مخفی کردن صفحه ثبت‌نام
            mainW->show(); // نمایش پنجره اصلی
        }
        else
        {
            QMessageBox::warning(this, "خطا", "ثبت‌نام ناموفق بود. لطفاً دوباره امتحان کنید.");
            qWarning() << "خطا در به‌روزرسانی اطلاعات کاربر: " << query.lastError().text();
        }
    }
    else
    {
        QMessageBox::warning(this, "خطا", "ثبت‌نام ناموفق بود. لطفاً دوباره امتحان کنید.");
        qWarning() << "خطا در افزودن کاربر به دیتابیس";
    }
}

