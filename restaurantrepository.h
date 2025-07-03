#ifndef RESTAURANTREPOSITORY_H
#define RESTAURANTREPOSITORY_H

#include <QString>
#include <QJsonArray>

    // کلاسی برای مدیریت عملیات مربوط به رستوران‌ها
    class RestaurantRepository {
public:
    // اضافه کردن رستوران جدید
    bool addRestaurant(int ownerId, const QString& name, const QString& address, const QString& startTime, const QString& endTime);

    // گرفتن لیست رستوران‌های یک صاحب خاص
    QJsonArray getRestaurantsByOwner(int ownerId);

    // تغییر وضعیت رستوران (توسط ادمین)
    bool updateRestaurantStatus(int restaurantId, const QString& status);

    // بررسی مالکیت رستوران
    bool isRestaurantOwner(int userId, int restaurantId);

    // گرفتن شناسه صاحب رستوران
    int getRestaurantOwnerId(int restaurantId);

    //حالت لود کردن رستوران ها
    QList<QMap<QString, QVariant>> Database::getAllRestaurants();
};

#endif // RESTAURANTREPOSITORY_H
