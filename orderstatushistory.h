#ifndef ORDERSTATUSHISTORY_H
#define ORDERSTATUSHISTORY_H

#include <QDateTime>
#include <QList>

//  تاریخچه وضعیت سفارش
class OrderStatusHistory
{
public:
    struct StatusChange {
        QDateTime timestamp;
        QString status;
    };

    void addStatusChange(const QString& status); // افزودن وضعیت جدید
    QList<StatusChange> getHistory() const { return history; } // دریافت تاریخچه

private:
    QList<StatusChange> history; // لیست تغییرات
};

#endif // ORDERSTATUSHISTORY_H
