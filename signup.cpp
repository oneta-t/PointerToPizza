#include "signup.h"
#include "ui_signup.h"

SignUP::SignUP(MainWindow* mainW,QWidget *parent): QWidget(parent), ui(new Ui::SignUP),mainW(mainW)
{
    ui->setupUi(this);
}

SignUP::~SignUP()
{
    delete ui;
}

void SignUP::on_pushButtoYes_clicked()
{
    QString name=ui->lineEdit_name->text().trimmed();
    QString family = ui->lineEdit_family->text().trimmed();
    QString username = ui->lineEdit_usernem->text().trimmed();
    QString password1 = ui->lineEdit_pass->text().trimmed();
    QString password2=ui->lineEdit_pass_2->text().trimmed();
    QString phone= ui->lineEdit_phon->text().trimmed();
    QString role=ui->comboBoxType->currentText();
    if (name.isEmpty() || family.isEmpty() || username.isEmpty() || password1.isEmpty() || phone.isEmpty() ||ui->comboBoxType->currentIndex() == 0)
    {
        QMessageBox::warning(this, "خطا", "لطفاً همه‌ی فیلدها را پر کنید");
        return;
    }
    if(password1!=password2)
    {
        QMessageBox::warning(this,"خطا", "رمز و تکرار آن یکسان نیست.لطفا دوباره امتحان کنید");
        return;
    }

    UserRepository userRepo; // ایجاد یک نمونه از UserRepository

    // بررسی وجود نام کاربری
    if (userRepo.userExists(username))
    {
        QMessageBox::warning(this, "خطا", "نام کاربری قبلاً وجود دارد.");
        return; // اگر نام کاربری وجود داشته باشد، از ادامه اجرای کد جلوگیری می‌کند.
    }

    if (role == "مشتری")
    {
        if (userRepo.userExists(username))
        {
            QMessageBox::warning(this, "خطا", "نام کاربری قبلاً وجود دارد.");
            return;
        }

        // اضافه کردن کاربر به پایگاه داده
        if (userRepo.addUser(username, password1, "مشتری"))
        {
            QMessageBox::information(this, "ثبت‌نام موفق", "ثبت‌نام با موفقیت انجام شد!");
            this->hide();
            mainW->show();
        } else {
            QMessageBox::warning(this, "خطا", "ثبت‌نام ناموفق بود. لطفاً دوباره امتحان کنید.");
        }
    }

    if (role == "مدیر رستوران") {
        if (userRepo.userExists(username))
        {
            QMessageBox::warning(this, "خطا", "نام کاربری قبلاً وجود دارد.");
            return;
        }

        // اضافه کردن مدیر رستوران به پایگاه داده
        if (userRepo.addUser(username, password1, "مدیر رستوران"))
        {
            QMessageBox::information(this, "ثبت‌نام موفق", "ثبت‌نام با موفقیت انجام شد!");
            this->hide();
            mainW->show();
        }
        else
        {
            QMessageBox::warning(this, "خطا", "ثبت‌نام ناموفق بود. لطفاً دوباره امتحان کنید.");
        }
    }
    this->hide();
    mainW->show();
}

