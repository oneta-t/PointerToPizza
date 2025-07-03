#include "customer.h"
#include <QLabel>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

// سازنده با اطلاعات کامل کاربر
Customer::Customer(int userId, const QString& name, const QString& family,
                   const QString& passw, const QString& username,
                   const QString& phone, const QString& role, QWidget *parent)
    : QWidget(parent), User(name, family, passw, username, phone, role),
    userId(userId), infPage(nullptr), cart(new Cart(this)), menuF(nullptr)
{
    setupUi();
}

// دestructor
Customer::~Customer()
{
}

// دریافت شناسه کاربر
int Customer::getUserId() const
{
    return userId;
}

// تنظیم رابط کاربری
void Customer::setupUi()
{
    // لیبل خوش‌آمدگویی با نام و نام خانوادگی کاربر
    QLabel* welcomeLabel = new QLabel("صفحه مشتری - خوش آمدید " + getFirstName() + " " + getLastName(), this);
    userInfoButton = new QPushButton("نمایش اطلاعات کاربر", this); // دکمه اطلاعات کاربر
    userInfoButton->setObjectName("UserInfButton");
    viewRestaurantsButton = new QPushButton("مشاهده رستوران‌ها", this); // دکمه نمایش رستوران‌ها
    viewRestaurantsButton->setObjectName("ViewRestaurantsButton");
    restaurantList = new QListWidget(this); // لیست رستوران‌ها

    // چیدمان عمودی
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(welcomeLabel);
    layout->addWidget(userInfoButton);
    layout->addWidget(viewRestaurantsButton);
    layout->addWidget(restaurantList);
    layout->addStretch();

    setLayout(layout);

    // اتصال سیگنال‌ها
    connect(userInfoButton, &QPushButton::clicked, this, &Customer::onUserInfoButtonClicked);
    connect(viewRestaurantsButton, &QPushButton::clicked, this, &Customer::onViewRestaurantsClicked);
    connect(restaurantList, &QListWidget::itemDoubleClicked, this, &Customer::onRestaurantSelected);
}

// نمایش اطلاعات کاربر
void Customer::onUserInfoButtonClicked()
{
    if (!infPage)
        infPage = new UserInformationPage(this);
    infPage->show();
}

// نمایش لیست رستوران‌ها
void Customer::onViewRestaurantsClicked()
{
    RestaurantRepository repo;
    QJsonArray restaurants = repo.getApprovedRestaurants();
    restaurantList->clear();

    // افزودن رستوران‌ها به لیست
    for (const QJsonValue& value : restaurants) {
        QJsonObject rest = value.toObject();
        QString itemText = QString("%1 - %2 (%3 تا %4)")
                               .arg(rest["name"].toString())
                               .arg(rest["location"].toString())
                               .arg(rest["startTime"].toString())
                               .arg(rest["endTime"].toString());
        QListWidgetItem* listItem = new QListWidgetItem(itemText, restaurantList);
        listItem->setData(Qt::UserRole, rest["id"].toInt());
    }
    restaurantList->show();
}

// نمایش منوی رستوران انتخاب‌شده
void Customer::onRestaurantSelected(QListWidgetItem* item)
{
    int restaurantId = item->data(Qt::UserRole).toInt();
    if (!menuF)
        menuF = new MenuF(restaurantId, this);
    else {
        menuF->deleteLater(); // حذف منوی قبلی
        menuF = new MenuF(restaurantId, this);
    }
    menuF->show();
    restaurantList->hide();
}
