#include "restaurantf.h"
#include "ui_restaurantf.h"
#include <QLabel>

RestaurantF::RestaurantF(int restaurantId, const QString& name, const QString& location,const QString& startTime, const QString& endTime, QWidget *parent)
    : QWidget(parent), restaurantId(restaurantId), name(name), location(location),
    startTime(startTime), endTime(endTime), menuF(nullptr), createF(new CreateFood(this))
{
    setupUi();
}

RestaurantF::~RestaurantF()
{
    delete menuF;
}

int RestaurantF::getRestaurantId() const { return restaurantId; }

QString RestaurantF::getName() const { return name; }

QString RestaurantF::getLocation() const { return location; }

QString RestaurantF::getStartTime() const { return startTime; }

QString RestaurantF::getEndTime() const { return endTime; }

MenuF* RestaurantF::getMenuF() const { return menuF; }

void RestaurantF::setupUi()
{
    // ایجاد ویجت‌ها
    QLabel* nameLabel = new QLabel("نام رستوران: " + name, this);
    QLabel* locationLabel = new QLabel("آدرس: " + location, this);
    QLabel* hoursLabel = new QLabel("ساعات کاری: " + startTime + " تا " + endTime, this);
    addMenuButton = new QPushButton("افزودن منو", this);
    addMenuButton->setObjectName("AddMenuButton");

    // تنظیم چیدمان عمودی
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(locationLabel);
    layout->addWidget(hoursLabel);
    layout->addWidget(addMenuButton);
    layout->addStretch();

    setLayout(layout);

    // اتصال سیگنال به اسلات
    connect(addMenuButton, &QPushButton::clicked, this, &RestaurantF::onAddMenuClicked);
}

void RestaurantF::onAddMenuClicked()
{
    createF->show();
    this->hide();
}

