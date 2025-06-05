#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// گرفتن تنها نمونه از کلاس
Database& Database::instance() {
    static Database instance;
    return instance;
}

// سازنده کلاس - اتصال به دیتابیس SQLite
Database::Database() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("iut_food.db");

    if (!db.open()) {
        qCritical() << "Cannot open database:" << db.lastError().text();
    } else {
        qDebug() << "Database connected.";
    }
}

// گرفتن اتصال دیتابیس
QSqlDatabase& Database::getConnection() {
    return db;
}

// ساخت جداول اولیه (در صورت نبود)
void Database::setupTables() {
    QSqlQuery query(db);

    QString createUserTable = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            role TEXT NOT NULL
        )
    )";

    if (!query.exec(createUserTable)) {
        qCritical() << "Failed to create users table:" << query.lastError().text();
    } else {
        qDebug() << "Users table ready.";
    }

    // اینجا می‌تونی جدول‌های دیگه مثل order, restaurant رو بعداً اضافه کنی
}
