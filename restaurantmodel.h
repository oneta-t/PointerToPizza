#ifndef RESTAURANTMODEL_H
#define RESTAURANTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "restaurantf.h"

class RestaurantModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // تعریف نام‌های نقش برای دسترسی به داده‌ها
    enum RoleNames
    {
        NameRole = Qt::UserRole + 1, // نام رستوران
        LocationRole,                 // آدرس رستوران
        StartTimeRole,                // ساعت شروع
        EndTimeRole                   // ساعت پایان
    };

    // سازنده مدل
    explicit RestaurantModel(QObject *parent = nullptr);

    // تابعی برای اضافه کردن رستوران به مدل
    void addRestaurant(RestaurantF *restaurant);

    // تعداد رستوران‌ها
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // دریافت داده‌های رستوران بر اساس ایندکس
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // تعریف نقش‌های مدل
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<RestaurantF*> m_restaurants; // لیست رستوران‌ها
};

#endif // RESTAURANTMODEL_H
