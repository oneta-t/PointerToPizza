#include "userrepository.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QCryptographicHash>

// افزودن کاربر جدید در دیتابیس
bool UserRepository::addUser(const QString& username, const QString& password, const QString& role) {
    QSqlQuery query(Database::instance().getConnection());

    // هش کردن رمز عبور با الگوریتم SHA256
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    query.prepare("INSERT INTO users (username, password, role) VALUES (:username, :password, :role)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":role", role);

    if (!query.exec()) {
        qWarning() << "Add user failed:" << query.lastError().text();
        return false;
    }

    return true;
}

// بررسی وجود کاربر در دیتابیس
bool UserRepository::userExists(const QString& username) {
    QSqlQuery query(Database::instance().getConnection());

    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qWarning() << "Add user failed:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}

// اعتبارسنجی اطلاعات ورود کاربر
bool UserRepository::validateLogin(const QString& username, const QString& password, int& userId, QString& role) {
    QSqlQuery query(Database::instance().getConnection());

    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    // هش کردن رمز عبور برای مقایسه با مقدار ذخیره شده
    query.prepare("SELECT id, role FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qWarning() << "Login failed:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        userId = query.value("id").toInt();
        role = query.value("role").toString();
        return true;
    }

    return false;
}
