#ifndef RESTAURANTREPOSITORY_H
#define RESTAURANTREPOSITORY_H

#include <QString>
#include <QJsonArray>
#include "RestaurantF.h"

// کلاسی برای مدیریت عملیات مربوط به رستوران‌ه
class RestaurantRepository {
public:

    // اضافه کردن رستوران جدید
    bool addRestaurant(int ownerId, const QString& name, const QString& location,const QString& startTime, const QString& endTime);

    // گرفتن لیست رستوران‌های تأییدشده
    QJsonArray getApprovedRestaurants();

    // گرفتن لیست رستوران‌های تأییدشده
    QJsonArray getApprovedRestaurants();

    // بررسی مالکیت رستوران
    bool isRestaurantOwner(int userId, int restaurantId);

    // گرفتن شناسه صاحب رستوران
    int getRestaurantOwnerId(int restaurantId);


    RestaurantF* getRestaurantInfo(int restaurantId);
};

#endif // RESTAURANTREPOSITORY_H
