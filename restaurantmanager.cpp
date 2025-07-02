#include "RestaurantManager.h"
#include <QLabel>

RestaurantManager::RestaurantManager(int userId, QWidget *parent)
    : QWidget(parent), User(), userId(userId), restaurantModel(new RestaurantModel(this)),
    registration(nullptr)
{
    setupUi();
}

RestaurantManager::RestaurantManager(int userId, const QString& name, const QString& family,const QString& passw, const QString& username,
                                     const QString& phone, const QString& role)
    : QWidget(nullptr), User(name, family, passw, username, phone, role),
    userId(userId), restaurantModel(new RestaurantModel(this)), registration(nullptr)
{
    setupUi();
}

RestaurantManager::~RestaurantManager()
{
    // restaurantModel و registration توسط Qt مدیریت می‌شوند
}

int RestaurantManager::getUserId() const
{
    return userId;
}

void RestaurantManager::setupUi()
{
    // ایجاد ویجت‌ها
    addRestaurantButton = new QPushButton("افزودن رستوران", this);
    addRestaurantButton->setObjectName("AddRestaurant");

    // تنظیم چیدمان عمودی
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("صفحه مدیر رستوران", this));
    layout->addWidget(addRestaurantButton);
    layout->addStretch();

    setLayout(layout);

    // اتصال سیگنال به اسلات
    connect(addRestaurantButton, &QPushButton::clicked, this, &RestaurantManager::onAddRestaurantClicked);
}

void RestaurantManager::onAddRestaurantClicked()
{
    if (!registration)
        registration = new RestaurantRegistration(this);
    registration->show();
}
