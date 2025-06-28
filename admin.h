#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include "user.h"
#include "restaurant.h"
#include "FoodDeliverySystem.h"
namespace Ui {
class Admin;
}


class Admin : public User
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    Admin(QString name, QString family, QString passw, QString username, QString phone, QString role);
    ~Admin();


    void verifyRestaurant(Restaurant* restaurant, bool isVerified); //  تأیید رستوران
    void banUser(const QString& username);
    void generateReports() const;

    // متدهای اضافی
    void viewUsers(); //  نمایش کاربران
    void deleteUser(const QString& username);

private:
    Ui::Admin *ui; //  رابط کاربری
    FoodDeliverySystem* deliverySystem; //  دسترسی به سیستم
};

#endif // ADMIN_H
