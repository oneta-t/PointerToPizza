#include "RestaurantLogin.h"
#include "ui_RestaurantLogin.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

RestaurantLogin::RestaurantLogin(QWidget *parent) : QWidget(parent), ui(new Ui::RestaurantLogin), db(QSqlDatabase::addDatabase("QSQLITE")) {
    ui->setupUi(this); // راه‌اندازی رابط
    connect(ui->loginButton, &QPushButton::clicked, this, &RestaurantLogin::handleLogin); // اتصال دکمه

    // تنظیم دیتابیس
    db.setDatabaseName("restaurant.db"); // نام دیتابیس
    if (!db.open()) {
        QMessageBox::critical(this, "خطا", "دیتابیس باز نشد: " + db.lastError().text());
    } else {
        // ایجاد جدول
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS owners ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "username TEXT NOT NULL, "
                   "password TEXT NOT NULL)");
        query.exec("INSERT OR IGNORE INTO owners (username, password) VALUES ('rest1', 'pass123')");
        query.exec("INSERT OR IGNORE INTO owners (username, password) VALUES ('rest2', 'pass456')");
    }
}

RestaurantLogin::~RestaurantLogin() {
    delete ui; // پاک کردن رابط
    db.close(); // بستن دیتابیس
}

void RestaurantLogin::handleLogin() {
    QString username = ui->usernameEdit->text(); // گرفتن نام کاربری
    QString password = ui->passwordEdit->text(); // گرفتن رمز

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "خطا", "لطفاً نام و رمز را وارد کن!"); // هشدار خالی
        return;
    }

    // بررسی ورود از دیتابیس
    QSqlQuery query;
    query.prepare("SELECT id FROM owners WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec() && query.next()) {
        QMessageBox::information(this, "موفق", "لاگین موفق!"); // تست پیام
        emit loginSuccess(query.value(0).toInt()); // ارسال سیگنال
    } else {
        QMessageBox::warning(this, "خطا", "نام یا رمز اشتباهه!"); // هشدار اشتباه
    }
}
