#ifndef RESTAURANTMODEL_H
#define RESTAURANTMODEL_H

#include <QAbstractListModel>
#include "restaurantf.h"
#include "restaurantrepository.h"

    // مدل برای نمایش رستوران‌ها در لیست
    class RestaurantModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit RestaurantModel(QObject *parent = nullptr);
    ~RestaurantModel();

    // متدهای مدل
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // اضافه کردن رستوران
    bool addRestaurant(RestaurantF *restaurant);

    // لود رستوران‌های یک صاحب
    void loadRestaurants(int ownerId);

private:
    QList<RestaurantF*> restaurants; // لیست رستوران‌ها
    RestaurantRepository repo;       // مخزن برای دسترسی به دیتابیس
};

#endif // RESTAURANTMODEL_H
