#include "customer.h"
#include "ui_customer.h"

Customer::~Customer()
{
    delete ui;
}

void Customer::on_UserInfButton_clicked()
{
    this->hide();
    this->InfPage->show();
}

#include "customer.h"
#include "ui_customer.h"
#include "userrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// سازنده کلاس Customer
Customer::Customer(int userId, QWidget *parent) : QWidget(parent), User(userId), ui(new Ui::Customer)
{
    ordersHistory=nullptr;
    // راه‌اندازی رابط کاربری
    ui->setupUi(this);
    // ایجاد صفحه اطلاعات کاربر
    this->InfPage = new UserInformationPage(this);
    // ایجاد سبد خرید
    this->cart = new Cart(this);

    // استخراج اطلاعات کاربر از دیتابیس با استفاده از userId
    QSqlQuery query;
    query.prepare("SELECT name, family, username, phone, role FROM users WHERE id = :userId");
    query.bindValue(":userId", userId);
    if (query.exec() && query.next()) {
        setName(query.value("name").toString());
        setFamily(query.value("family").toString());
        setUsername(query.value("username").toString());
        setPhone(query.value("phone").toString());
        setRole(query.value("role").toString());
    }
    else {
        qWarning() << "خطا در استخراج اطلاعات کاربر: " << query.lastError().text();
    }
}

// دستراکتور برای آزادسازی منابع
Customer::~Customer()
{
    delete ui;
    delete InfPage;
    delete cart;
    qDeleteAll(ordersHistory);
}

// مدیریت کلیک روی دکمه اطلاعات کاربر
void Customer::on_UserInfButton_clicked()
{
    this->hide(); // مخفی کردن صفحه مشتری
    this->InfPage->show(); // نمایش صفحه اطلاعات کاربر
}

void Customer::loadRestaurants()
{
    restaurantModel->loadRestaurants(-1); // -1 برای همه رستوران‌های تأییدشده
}

// لود منوی رستوران
void Customer::loadMenu(int restaurantId)
{
    if (currentMenu) {
        delete currentMenu;
    }
    currentMenu = new MenuF(restaurantId, this);
    currentMenu->show();
    this->hide();
}
