#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include "User.h"
#include "UserInformationPage.h"
#include "Cart.h"
#include "RestaurantRepository.h"
#include "MenuF.h"

// کلاس صفحه مشتری با ارث‌بری از User
class Customer : public QWidget, public User
{
    Q_OBJECT

public:
    // سازنده با اطلاعات کامل کاربر
    explicit Customer(int userId, const QString& name, const QString& family,
                      const QString& passw, const QString& username,
                      const QString& phone, const QString& role, QWidget *parent = nullptr);
    // دریافت شناسه کاربر
    int getUserId() const;
    // دestructor
    ~Customer();

private slots:
    // نمایش اطلاعات کاربر
    void onUserInfoButtonClicked();
    // نمایش لیست رستوران‌ها
    void onViewRestaurantsClicked();
    // نمایش منوی رستوران انتخاب‌شده
    void onRestaurantSelected(QListWidgetItem* item);

private:
    // تنظیم رابط کاربری
    void setupUi();

    int userId; // شناسه کاربر
    QPushButton* userInfoButton; // دکمه اطلاعات کاربر
    QPushButton* viewRestaurantsButton; // دکمه نمایش رستوران‌ها
    QListWidget* restaurantList; // لیست رستوران‌ها
    UserInformationPage* infPage; // صفحه اطلاعات کاربر
    Cart* cart; // سبد خرید
    MenuF* menuF; // صفحه منوی رستوران
};

#endif // CUSTOMER_H
