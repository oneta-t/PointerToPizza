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

    User *newUser = new User(name, family, password1, username, phone, role);

    QMessageBox::information(this, "ثبت‌نام موفق", "ثبت‌نام با موفقیت انجام شد!");
    this->hide();
    mainW->show();
}

