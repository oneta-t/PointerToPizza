#include "admin.h"
#include "ui_admin.h"
#include <QMessageBox>
#include <QListWidget>

Admin::Admin(QWidget *parent)
    : User("Admin", "", "adminpass", "admin", "000", "admin"), ui(new Ui::Admin), deliverySystem(FoodDeliverySystem::getInstance())
{
    ui->setupUi(this); //  تنظیم رابط

    // اتصال دکمه‌ها
    connect(ui->viewUsersButton, &QPushButton::clicked, this, &Admin::viewUsers);
    connect(ui->banButton, &QPushButton::clicked, this, [&]() {
        if (ui->userList->currentItem()) banUser(ui->userList->currentItem()->text());
    });
    connect(ui->deleteButton, &QPushButton::clicked, this, [&]() {
        if (ui->userList->currentItem()) deleteUser(ui->userList->currentItem()->text());
    });
    connect(ui->verifyButton, &QPushButton::clicked, this, [&]() {
        if (ui->restaurantList->currentItem()) {
            Restaurant* rest = reinterpret_cast<Restaurant*>(ui->restaurantList->currentItem()->data(Qt::UserRole).value<void*>());
            verifyRestaurant(rest, ui->verifyCheck->isChecked());
        }
    });
}

Admin::Admin(QString name, QString family, QString passw, QString username, QString phone, QString role)
    : User(name, family, passw, username, phone, role), ui(new Ui::Admin), deliverySystem(FoodDeliverySystem::getInstance())
{
    ui->setupUi(this);
}

Admin::~Admin()
{
    delete ui; //  پاک‌سازی
}

void Admin::verifyRestaurant(Restaurant* restaurant, bool isVerified)
{
    if (restaurant) {
        restaurant->setVerified(isVerified);
        QMessageBox::information(this, "تأیید", QString("رستوران %1 %2 شد.").arg(restaurant->getName()).arg(isVerified ? "تأیید" : "رد"));
    }
}

void Admin::banUser(const QString& username)
{
    for (User* user : deliverySystem->getUsers()) {
        if (user->getUsername() == username) {
            user->setRole("banned");
            QMessageBox::information(this, "بلاک", QString("کاربر %1 بلاک شد.").arg(username));
            viewUsers();
            return;
        }
    }
    QMessageBox::warning(this, "خطا", "کاربر یافت نشد!");
}

void Admin::generateReports() const
{
    QMessageBox::information(this, "گزارش", QString("کاربران: %1, رستوران‌ها: %2").arg(deliverySystem->getUsers().size()).arg(deliverySystem->getRestaurants().size()));
}

void Admin::viewUsers()
{
    ui->userList->clear();
    for (User* user : deliverySystem->getUsers()) {
        if (user->getRole() != "banned") {
            ui->userList->addItem(user->getUsername()); //  نمایش کاربران
        }
    }
}

void Admin::deleteUser(const QString& username)
{
    for (int i = 0; i < deliverySystem->getUsers().size(); ++i) {
        if (deliverySystem->getUsers()[i]->getUsername() == username) {
            delete deliverySystem->getUsers().takeAt(i);
            QMessageBox::information(this, "حذف", QString("کاربر %1 حذف شد.").arg(username));
            viewUsers();
            return;
        }
    }
    QMessageBox::warning(this, "خطا", "کاربر یافت نشد!");
}
