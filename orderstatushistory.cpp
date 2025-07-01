#include "orderstatushistory.h"

void OrderStatusHistory::addStatusChange(const QString& status)
{
    StatusChange change;
    change.timestamp = QDateTime::currentDateTime(); // زمان فعلی
    change.status = status; // کامنت: ذخیره وضعیت
    history.append(change);
}
