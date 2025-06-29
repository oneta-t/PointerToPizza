#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// پیاده سازی Singleton
Database& Database::instance() {
    static Database instance;
    return instance;
}

// سازنده کلاس Database
Database::Database() {
    // استفاده از درایو SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("iut_food.db");

    // تلاش برای اتصال به دیتابیس
    if (!db.open()) {
        qCritical() << "Cannot open database:" << db.lastError().text();
        exit(1); // خاتمه برنامه
    } else {
        qDebug() << "Database connected.";
    }
}
// برگرداندن اتصال دیتابیس
QSqlDatabase& Database::getConnection() {
    return db;
}

// ایجاد جداول دیتابیس
void Database::setupTables() {
    QSqlQuery query(db);

    // ایجاد جدول کاربران
    QString createUserTable = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            role TEXT NOT NULL CHECK(role IN ('customer', 'restaurant_owner', 'admin'))
        )
    )";
    if (!query.exec(createUserTable)) {
        qCritical() << "Failed to create users table:" << query.lastError().text();
    }

    // ایجاد جدول رستوران ها
    QString createRestaurantTable = R"(
        CREATE TABLE IF NOT EXISTS restaurants (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE NOT NULL,
            owner_id INTEGER NOT NULL,
            status TEXT NOT NULL CHECK(status IN ('pending', 'approved', 'rejected')),
            FOREIGN KEY (owner_id) REFERENCES users(id)
        )
    )";
    if (!query.exec(createRestaurantTable)) {
        qCritical() << "Failed to create restaurants table:" << query.lastError().text();
    }

    // ایجاد جدول سفارش ها
    QString createOrderTable = R"(
        CREATE TABLE IF NOT EXISTS orders (
            order_id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            restaurant_id INTEGER NOT NULL,
            status TEXT NOT NULL CHECK(status IN ('pending', 'preparing', 'delivered')),
            create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (user_id) REFERENCES users(id),
            FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)
        )
    )";
    if (!query.exec(createOrderTable)) {
        qCritical() << "Failed to create orders table:" << query.lastError().text();
    }

    // ایجاد جدول آیتم های سفارش
    QString createOrderItemsTable = R"(
        CREATE TABLE IF NOT EXISTS order_items (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            order_id INTEGER NOT NULL,
            item_id INTEGER NOT NULL,
            quantity INTEGER NOT NULL,
            FOREIGN KEY (order_id) REFERENCES orders(order_id)
        )
    )";
    if (!query.exec(createOrderItemsTable)) {
        qCritical() << "Failed to create order_items table:" << query.lastError().text();
    } else {
        qDebug() << "All tables are set up correctly.";
    }
}
