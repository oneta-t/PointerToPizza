#include "Customer.h"
#include <QLabel>

Customer::Customer(int userId, QWidget *parent)
    : QWidget(parent), User(), userId(userId), infPage(nullptr), cart(new Cart(this))
{
    setupUi();
}

Customer::Customer(int userId, const QString& name, const QString& family, const QString& passw,
                   const QString& username, const QString& phone, const QString& role)
    : QWidget(nullptr), User(name, family, passw, username, phone, role),
    userId(userId), infPage(nullptr), cart(new Cart(this))
{
    setupUi();
}

Customer::~Customer()
{
    // cart و infPage توسط Qt مدیریت می‌شوند (والد دارند)
}

int Customer::getUserId() const
{
    return userId;
}

void Customer::setupUi()
{
    // ایجاد ویجت‌ها
    userInfoButton = new QPushButton("نمایش اطلاعات کاربر", this);
    userInfoButton->setObjectName("UserInfButton");

    // تنظیم چیدمان عمودی
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("صفحه مشتری", this));
    layout->addWidget(userInfoButton);
    layout->addStretch();

    setLayout(layout);

    // اتصال سیگنال به اسلات
    connect(userInfoButton, &QPushButton::clicked, this, &Customer::onUserInfoButtonClicked);
}

void Customer::onUserInfoButtonClicked()
{
    if (!infPage)
        infPage = new UserInformationPage(this);
    infPage->show();
}
