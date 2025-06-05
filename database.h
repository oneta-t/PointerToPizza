#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>

class Database {
public:
    // تابعی برای گرفتن تنها نمونه از این کلاس (Singleton)
    static Database& instance();

    // گرفتن اتصال دیتابیس
    QSqlDatabase& getConnection();

    // ساخت جداول اولیه مثل users
    void setupTables();

private:
    Database(); // سازنده خصوصی
    QSqlDatabase db; // اتصال به دیتابیس
};

#endif // DATABASE_H
