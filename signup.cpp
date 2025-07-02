#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>

SignUP::SignUP(MainWindow* mainW, QWidget *parent)
    : QWidget(parent), ui(new Ui::SignUP), mainW(mainW)
{
    ui->setupUi(this);
}

SignUP::~SignUP()
{
    delete ui;
}

void SignUP::on_pushButtoYes_clicked()
{
    QString username = ui->lineEdit_username->text().trimmed();
    QString password = ui->lineEdit_password->text().trimmed();
    QString name = ui->lineEdit_name->text().trimmed();
    QString family = ui->lineEdit_family->text().trimmed();
    QString phone = ui->lineEdit_phone->text().trimmed();
    QString role = ui->comboBox_role->currentText().trimmed(); // یا ui->lineEdit_role

    if (username.isEmpty() || password.isEmpty() || name.isEmpty() || family.isEmpty() || phone.isEmpty() || role.isEmpty()) {
        QMessageBox::warning(this, "خطا", "لطفاً تمام فیلدها را پر کنید.");
        return;
    }

    UserRepository userRepo;
    if (userRepo.userExists(username)) {
        QMessageBox::warning(this, "خطا", "نام کاربری قبلاً وجود دارد!");
        return;
    }

    if (userRepo.addUser(username, password, role, name, family, phone)) {
        QMessageBox::information(this, "موفقیت", "کاربر با موفقیت ثبت شد.");
        this->hide();
        mainW->show();
    } else {
        QMessageBox::warning(this, "خطا", "ثبت کاربر ناموفق بود.");
    }
}

