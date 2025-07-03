#include "restaurantmanager.h"
#include "ui_restaurantmanager.h"
#include "userrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// سازنده کلاس RestaurantManager
RestaurantManager::RestaurantManager(int userId, QWidget *parent) : QWidget(parent), User(userId), ui(new Ui::RestaurantManager)
{
    restaurants=nullptr;
    // راه‌اندازی رابط کاربری
    ui->setupUi(this);
    // ایجاد صفحه ثبت رستوران
    this->Registration = new RestaurantRegistration(this);
    // ایجاد مدل رستوران‌ها
    this->restaurantModel = new RestaurantModel(this);
    // اتصال مدل به لیست ویو
    ui->listViewRestaurants->setModel(restaurantModel);

    // استخراج اطلاعات مدیر از دیتابیس با استفاده از userId
    QSqlQuery query;
    query.prepare("SELECT name, family, username, phone, role FROM users WHERE id = :userId");
    query.bindValue(":userId", userId);
    if (query.exec() && query.next()) {
        setName(query.value("name").toString());
        setFamily(query.value("family").toString());
        setUsername(query.value("username").toString());
        setPhone(query.value("phone").toString());
        setRole(query.value("role").toString());
    } else {
        qWarning() << "خطا در استخراج اطلاعات مدیر: " << query.lastError().text();
    }
}

// دستراکتور برای آزادسازی منابع
RestaurantManager::~RestaurantManager()
{
    delete ui;
    delete Registration;
    delete restaurantModel;
    qDeleteAll(restaurants);
}

// مدیریت کلیک روی دکمه افزودن رستوران
void RestaurantManager::on_AddRestaurant_clicked()
{
    this->hide();
    this->Registration->show();
}

void RestaurantManager::loadRestaurants()
{
    restaurantModel->loadRestaurants(userId);
}


