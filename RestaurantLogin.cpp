#include "RestaurantLogin.h"
#include "ui_RestaurantLogin.h"
#include <QMessageBox>

const RestaurantLogin:: { QString username; QString password; int id; } RestaurantLogin::restaurantUsers[] = {
    {"rest1", "pass123", 1},
    {"rest2", "pass456", 2}
};
const int RestaurantLogin::userCount = 2;

RestaurantLogin::RestaurantLogin(QWidget *parent)
    : User("Restaurant", "", "123", "rest0", "000", "restaurant"), // سازنده User با مقادیر پیش‌فرض
    ui(new Ui::RestaurantLogin) {
    ui->setupUi(this); // راه‌اندازی رابط کاربری
    connect(ui->loginButton, &QPushButton::clicked, this, &RestaurantLogin::handleLogin); // اتصال دکمه
}

RestaurantLogin::~RestaurantLogin() {
    delete ui; // آزادسازی حافظه
}

void RestaurantLogin::handleLogin() {
    QString username = ui->usernameEdit->text(); // دریافت نام کاربری
    QString password = ui->passwordEdit->text(); // دریافت رمز عبور

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "خطا", "لطفاً نام کاربری و رمز عبور را وارد کنید."); // هشدار فیلد خالی
        return;
    }

    for (int i = 0; i < userCount; ++i) {
        if (restaurantUsers[i].username == username && restaurantUsers[i].password == password) {
            emit loginSuccess(restaurantUsers[i].id); // ارسال شناسه در صورت موفقیت
            return;
        }
    }
    QMessageBox::warning(this, "خطا", "نام کاربری یا رمز عبور نادرست است."); // هشدار ورود ناموفق
}
