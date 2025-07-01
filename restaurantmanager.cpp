#include "restaurantmanager.h"
#include "ui_restaurantmanager.h"
#include <QMessageBox>

/*RestaurantManager::RestaurantManager(QWidget *parent): QWidget(parent), ui(new Ui::RestaurantManager)
{
    ui->setupUi(this);
}

RestaurantManager::~RestaurantManager()
{
    delete ui;
}

int RestaurantManager::NextId=0;

RestaurantManager::RestaurantManager(QString name,QString family,QString passw,QString username,QString phone,QString role):User(name,family,passw,username,phone,role){}*/

//همون کد بالا رو یه سری جزعیات اضافه کردم


RestaurantManager::RestaurantManager(QWidget *parent)
    : QWidget(parent), ui(new Ui::RestaurantManager), restaurantModel(new RestaurantModel(this))
{
    ui->setupUi(this);
    this->Registration = new RestaurantRegistration(this);
    ui->listViewRestaurants->setModel(restaurantModel); // اتصال مدل به QListView
    orderManager = new RealTimeOrderManager(this, this); // ایجاد مدیر سفارش
    connect(orderManager, &RealTimeOrderManager::newOrderGenerated, this, &RestaurantManager::handleNewOrder); //  اتصال سیگنال
    connect(ui->updateStatusButton, &QPushButton::clicked, this, &RestaurantManager::on_UpdateStatus_clicked); //  اتصال دکمه
}

RestaurantManager::~RestaurantManager()
{
    delete ui;
    delete Registration;
    delete orderManager; //  پاک‌سازی مدیر سفارش
    qDeleteAll(orders); //  پاک‌سازی سفارش‌ها
}

int RestaurantManager::NextIdRM = 0;

RestaurantManager::RestaurantManager(QString name, QString family, QString passw, QString username, QString phone, QString role)
    : User(name, family, passw, username, phone, role), ui(new Ui::RestaurantManager), restaurantModel(new RestaurantModel(this))
{
    IdRM = NextIdRM++;
}

void RestaurantManager::on_AddRestaurant_clicked()
{
    this->hide();
    this->Registration->show();
}

void RestaurantManager::handleNewOrder(Order* order)
{
    if (order) {
        orders.append(order); // اضافه کردن سفارش به لیست
        QMessageBox::information(this, "سفارش جدید", QString("سفارش بلادرنگ %1 دریافت شد.").arg(order->getId()));
      
    }
}

void RestaurantManager::on_UpdateStatus_clicked()
{
    if (ui->orderList->currentRow() >= 0 && ui->orderList->currentRow() < orders.size()) {
        Order* order = orders[ui->orderList->currentRow()];
        Order::Status currentStatus = order->getStatus();
        Order::Status newStatus = Order::Processing; // پیش‌فرض
        if (currentStatus == Order::Processing) newStatus = Order::Preparing;
        else if (currentStatus == Order::Preparing) newStatus = Order::Shipping;
        else if (currentStatus == Order::Shipping) newStatus = Order::Delivered;
        order->setStatus(newStatus);
        QMessageBox::information(this, "به‌روزرسانی", QString("وضعیت سفارش %1 به %2 تغییر کرد.").arg(order->getId()).arg(order->getStatusText()));
        
    } else {
        QMessageBox::warning(this, "خطا", "سفارشی انتخاب نشده است!");
    }
}
