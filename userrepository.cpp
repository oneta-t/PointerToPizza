#include "userrepository.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QCryptographicHash>

// افزودن کاربر جدید در دیتابیس
bool UserRepository::addUser(const QString& username, const QString& password, const QString& role,const QString& name, const QString& family, const QString& phone)
{
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    QSqlQuery query(Database::instance().getConnection());
    query.prepare("INSERT INTO users (username, password, role, name, family, phone) ""VALUES (:username, :password, :role, :name, :family, :phone)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);
    query.bindValue(":role", role);
    query.bindValue(":name", name);
    query.bindValue(":family", family);
    query.bindValue(":phone", phone);

    return query.exec();
}

UserRepository::UserRepository() {}

// بررسی وجود کاربر در دیتابیس
bool UserRepository::userExists(const QString& username)
{
    QSqlQuery query(Database::instance().getConnection());
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

// اعتبارسنجی اطلاعات ورود کاربر
bool UserRepository::validateLogin(const QString& username, const QString& password, int& userId, QString& role)
{
    QSqlQuery query(Database::instance().getConnection());
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    query.prepare("SELECT id, role FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

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

//لود کردن اطلاعات با استفاده از Id
{
    User user;
    QSqlQuery query(Database::instance().getConnection());
    query.prepare("SELECT name, family, username, phone, password, role FROM users WHERE id = :id");
    query.bindValue(":id", userId);

    if (query.exec() && query.next()) {
        user = User(
            query.value("name").toString(),
            query.value("family").toString(),
            query.value("password").toString(),
            query.value("username").toString(),
            query.value("phone").toString(),
            query.value("role").toString()
            );
    } else {
        qWarning() << "Failed to fetch user info:" << query.lastError().text();
    }

    return user;
}
