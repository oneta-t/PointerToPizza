#include "restaurantrepository.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>
#include <QDebug>

    // اضافه کردن رستوران جدید
    bool RestaurantRepository::addRestaurant(int ownerId, const QString& name, const QString& address, const QString& startTime, const QString& endTime) {
    QSqlQuery query(Database::instance().getConnection());

    query.prepare("INSERT INTO restaurants (name, owner_id, address, start_time, end_time, status) VALUES (:name, :owner_id, :address, :start_time, :end_time, 'pending')");
    query.bindValue(":name", name);
    query.bindValue(":owner_id", ownerId);
    query.bindValue(":address", address);
    query.bindValue(":start_time", startTime);
    query.bindValue(":end_time", endTime);

    if (!query.exec()) {
        qWarning() << "Failed to add restaurant:" << query.lastError().text();
        return false;
    }
    return true;
}

// گرفتن لیست رستوران‌های یک صاحب خاص
QJsonArray RestaurantRepository::getRestaurantsByOwner(int ownerId) {
    QSqlQuery query(Database::instance().getConnection());
    QJsonArray restaurantArray;

    query.prepare("SELECT id, name, address, start_time, end_time FROM restaurants WHERE owner_id = :ownerId AND status = 'approved'");
    query.bindValue(":ownerId", ownerId);
    if (query.exec()) {
        while (query.next()) {
            QJsonObject rest;
            rest["id"] = query.value("id").toInt();
            rest["name"] = query.value("name").toString();
            rest["address"] = query.value("address").toString();
            rest["start_time"] = query.value("start_time").toString();
            rest["end_time"] = query.value("end_time").toString();
            restaurantArray.append(rest);
        }
    } else {
        qWarning() << "Failed to retrieve restaurants:" << query.lastError().text();
    }
    return restaurantArray;
}

// تغییر وضعیت رستوران (توسط ادمین)
bool RestaurantRepository::updateRestaurantStatus(int restaurantId, const QString& status) {
    QSqlQuery query(Database::instance().getConnection());

    query.prepare("UPDATE restaurants SET status = :status WHERE id = :rid");
    query.bindValue(":status", status);
    query.bindValue(":rid", restaurantId);

    if (!query.exec()) {
        qWarning() << "Failed to update restaurant status:" << query.lastError().text();
        return false;
    }
    return true;
}

// بررسی مالکیت رستوران
bool RestaurantRepository::isRestaurantOwner(int userId, int restaurantId) {
    QSqlQuery query(Database::instance().getConnection());
    query.prepare("SELECT owner_id FROM restaurants WHERE id = :rid");
    query.bindValue(":rid", restaurantId);

    if (query.exec() && query.next()) {
        return query.value("owner_id").toInt() == userId;
    }
    return false;
}

// گرفتن شناسه صاحب رستوران
int RestaurantRepository::getRestaurantOwnerId(int restaurantId) {
    QSqlQuery query(Database::instance().getConnection());
    query.prepare("SELECT owner_id FROM restaurants WHERE id = :rid");
    query.bindValue(":rid", restaurantId);

    if (query.exec() && query.next()) {
        return query.value("owner_id").toInt();
    }
    return -1;
}

//برای لود کردن رستوران
QList<QMap<QString, QVariant>> Database::getAllRestaurants() {
    QList<QMap<QString, QVariant>> restaurants;
    QSqlQuery query(db);
    
    if (!query.exec("SELECT id, name, owner_id, address, status FROM restaurants")) {
        qCritical() << "Failed to fetch restaurants:" << query.lastError().text();
       LGPLv2.1return restaurants;
    }
    
    while (query.next()) {
        QMap<QString, QVariant> restaurant;
        restaurant["id"] = query.value("id").toInt();
        restaurant["name"] = query.value("name").toString();
        restaurant["owner_id"] = query.value("owner_id").toInt();
        restaurant["address"] = query.value("address").toString();
        restaurant["status"] = query.value("status").toString();
        restaurants.append(restaurant);
    }
    
    return restaurants;
}
