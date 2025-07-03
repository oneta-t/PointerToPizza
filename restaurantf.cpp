#include "restaurantf.h"
#include "ui_restaurantf.h"

// سازنده کلاس RestaurantF
RestaurantF::RestaurantF(int id, int ownerId, QString name, QString address, QString startTime, QString endTime, QWidget *parent)
    : QWidget(parent), ui(new Ui::RestaurantF), createF(new CreateFood(this)),
    id(id), ownerId(ownerId), name(name), address(address), startTime(startTime), endTime(endTime)
{
    ui->setupUi(this);
}

// دستراکتور برای آزادسازی منابع
RestaurantF::~RestaurantF()
{
    delete ui;
    delete createF; // آزادسازی صفحه ایجاد غذا
}

int RestaurantF::getId() const { return id; }

int RestaurantF::getOwnerId() const { return ownerId; }

QString RestaurantF::getName() const { return name; }

QString RestaurantF::getAddress() const { return address; }

QString RestaurantF::getStartTime() const { return startTime; }

QString RestaurantF::getEndTime() const { return endTime; }

MenuF* RestaurantF::getMenuF() const { return menuF; }

// مدیریت کلیک روی دکمه افزودن منو
void RestaurantF::on_addMenu_clicked()
{
    this->hide(); // پنهان کردن صفحه رستوران
    this->createF->show(); // نمایش صفحه ایجاد غذا
}
