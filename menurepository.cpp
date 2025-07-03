#include "MenuRepository.h"
#include "Database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>
#include <QDebug>

bool MenuRepository::addMenuItem(int restaurantId, const QString& name, double price, const QString& type, const QString& ingredients) {
    QSqlQuery query(Database::instance().getConnection());

    QRegularExpression validType("^(main_course|dessert|beverage)$");
    if (!validType.match(type).hasMatch()) {
        qWarning() << "Invalid menu item type:" << type;
        return false;
    }

    query.prepare("INSERT INTO menu_items (restaurant_id, name, price, type, ingredients) "
                  "VALUES (:rid, :name, :price, :type, :ingredients)");
    query.bindValue(":rid", restaurantId);
    query.bindValue(":name", name);
    query.bindValue(":price", price);
    query.bindValue(":type", type);
    query.bindValue(":ingredients", ingredients);

    if (!query.exec()) {
        qWarning() << "Failed to add menu item:" << query.lastError().text();
        return false;
    }
    return true;
}

bool MenuRepository::editMenuItem(int itemId, int restaurantId, const QString& name, double price, const QString& type, const QString& ingredients) {
    QSqlQuery query(Database::instance().getConnection());

    QRegularExpression validType("^(main_course|dessert|beverage)$");
    if (!validType.match(type).hasMatch()) {
        qWarning() << "Invalid menu item type:" << type;
        return false;
    }

    query.prepare("UPDATE menu_items SET name = :name, price = :price, type = :type, ingredients = :ingredients "
                  "WHERE id = :item_id AND restaurant_id = :rid");
    query.bindValue(":name", name);
    query.bindValue(":price", price);
    query.bindValue(":type", type);
    query.bindValue(":ingredients", ingredients);
    query.bindValue(":item_id", itemId);
    query.bindValue(":rid", restaurantId);

    if (!query.exec()) {
        qWarning() << "Failed to edit menu item:" << query.lastError().text();
        return false;
    }
    return true;
}

bool MenuRepository::deleteMenuItem(int itemId, int restaurantId) {
    QSqlQuery query(Database::instance().getConnection());

    query.prepare("DELETE FROM menu_items WHERE id = :item_id AND restaurant_id = :rid");
    query.bindValue(":item_id", itemId);
    query.bindValue(":rid", restaurantId);

    if (!query.exec()) {
        qWarning() << "Failed to delete menu item:" << query.lastError().text();
        return false;
    }
    return true;
}

QJsonArray MenuRepository::getMenu(int restaurantId) {
    QSqlQuery query(Database::instance().getConnection());
    QJsonArray menuArray;

    query.prepare("SELECT id, name, price, type, ingredients FROM menu_items WHERE restaurant_id = :rid");
    query.bindValue(":rid", restaurantId);

    if (query.exec()) {
        while (query.next()) {
            QJsonObject item;
            item["item_id"] = query.value("id").toInt();
            item["name"] = query.value("name").toString();
            item["price"] = query.value("price").toDouble();
            item["type"] = query.value("type").toString();
            item["ingredients"] = query.value("ingredients").toString();
            menuArray.append(item);
        }
    } else {
        qWarning() << "Failed to retrieve menu:" << query.lastError().text();
    }
    return menuArray;
}
