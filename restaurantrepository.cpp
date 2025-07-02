#include "RestaurantRepository.h"
#include "Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>
#include <QDebug>

bool RestaurantRepository::addRestaurant(int ownerId, const QString& name, const QString& location,
                                         const QString& startTime, const QString& endTime) {
    QSqlQuery query(Database::instance().getConnection());
    query.prepare("INSERT INTO restaurants (name, owner_id, status, location, start_time, end_time) ""VALUES (:name, :owner_id, 'pending', :location, :start_time, :end_time)");
    query.bindValue(":name", name);
    query.bindValue(":owner_id", ownerId);
    query.bindValue(":location", location);
    query.bindValue(":start_time", startTime);
    query.bindValue(":end_time", endTime);

    if (!query.exec()) {
        qWarning() << "Failed to add restaurant:" << query.lastError().text();
        return false;
    }
    return true;
}

QJsonArray RestaurantRepository::getApprovedRestaurants() {
    QSqlQuery query(Database::instance().getConnection());
    QJsonArray restaurantArray;

    if (query.exec("SELECT id, name, location, start_time, end_time FROM restaurants WHERE status = 'approved'")) {
        while (query.next()) {
            QJsonObject rest;
            rest["id"] = query.value("id").toInt();
            rest["name"] = query.value("name").toString();
            rest["location"] = query.value("location").toString();
            rest["startTime"] = query.value("start_time").toString();
            rest["endTime"] = query.value("end_time").toString();
            restaurantArray.append(rest);
        }
    } else {
        qWarning() << "Failed to retrieve restaurants:" << query.lastError().text();
    }
    return restaurantArray;
}

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

bool RestaurantRepository::isRestaurantOwner(int userId, int restaurantId) {
    QSqlQuery query(Database::instance().getConnection());
    query.prepare("SELECT owner_id FROM restaurants WHERE id = :rid");
    query.bindValue(":rid", restaurantId);

    if (query.exec() && query.next()) {
        return query.value("owner_id").toInt() == userId;
    }
    return false;
}

int RestaurantRepository::getRestaurantOwnerId(int restaurantId) {
    QSqlQuery query(Database::instance().getConnection());
    query.prepare("SELECT owner_id FROM restaurants WHERE id = :rid");
    query.bindValue(":rid", restaurantId);

    if (query.exec() && query.next()) {
        return query.value("owner_id").toInt();
    }
    return -1;
}

RestaurantF* RestaurantRepository::getRestaurantInfo(int restaurantId) {
    QSqlQuery query(Database::instance().getConnection());
    query.prepare("SELECT name, location, start_time, end_time FROM restaurants WHERE id = :rid");
    query.bindValue(":rid", restaurantId);

    if (query.exec() && query.next()) {
        return new RestaurantF(
            query.value("name").toString(),
            query.value("location").toString(),
            query.value("start_time").toString(),
            query.value("end_time").toString()
            );
    }
    qWarning() << "Failed to fetch restaurant info:" << query.lastError().text();
    return nullptr;
}
