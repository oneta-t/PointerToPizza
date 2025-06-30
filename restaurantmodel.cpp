#include "restaurantmodel.h"

// سازنده مدل
RestaurantModel::RestaurantModel(QObject *parent): QAbstractListModel(parent) {}

// تابع برای اضافه کردن رستوران
void RestaurantModel::addRestaurant(RestaurantF *restaurant)
{
    qDebug() << "Adding restaurant:" << restaurant->getName();
    beginInsertRows(QModelIndex(), rowCount(), rowCount()); // آغاز عملیات افزودن رستوران
    m_restaurants.append(restaurant); // افزودن رستوران به لیست
    endInsertRows(); // پایان عملیات
}

// تعداد رستوران‌ها
int RestaurantModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_restaurants.count(); // تعداد رستوران‌ها را برمی‌گرداند
}

// دریافت داده‌ها بر اساس ایندکس
QVariant RestaurantModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_restaurants.size())
        return QVariant(); // اگر ایندکس نامعتبر باشد، چیزی برنگردانید

    RestaurantF *restaurant = m_restaurants[index.row()]; // دریافت اشاره‌گر به رستوران

    switch (role) {
    case NameRole:
        return restaurant->getName(); // بازگشت نام رستوران
    case LocationRole:
        return restaurant->getLocation(); // بازگشت آدرس رستوران
    case StartTimeRole:
        return restaurant->getStartTime(); // بازگشت ساعت شروع
    case EndTimeRole:
        return restaurant->getEndTime(); // بازگشت ساعت پایان
    default:
        return QVariant(); // در غیر این صورت، چیزی برنگردانید
    }
}

// تعریف نقش‌ها
QHash<int, QByteArray> RestaurantModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name"; // نقش نام
    roles[LocationRole] = "location"; // نقش آدرس
    roles[StartTimeRole] = "startTime"; // نقش ساعت شروع
    roles[EndTimeRole] = "endTime"; // نقش ساعت پایان
    return roles; // بازگشت نقش‌ها
}
