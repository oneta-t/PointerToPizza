#include "restaurantmodel.h"

RestaurantModel::RestaurantModel(QObject *parent) : QAbstractListModel(parent)
{
}

RestaurantModel::~RestaurantModel()
{
    qDeleteAll(restaurants); // آزادسازی همه رستوران‌ها
}

int RestaurantModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return restaurants.count();
}

QVariant RestaurantModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && index.row() < restaurants.count()) {
        RestaurantF *restaurant = restaurants.at(index.row());
        return QString("%1 - %2").arg(restaurant->getName(), restaurant->getAddress());
    }
    return QVariant();
}

bool RestaurantModel::addRestaurant(RestaurantF *restaurant)
{
    if (!restaurant) return false;
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    restaurants.append(restaurant);
    endInsertRows();
    return true;
}

void RestaurantModel::loadRestaurants(int ownerId)
{
    beginResetModel();
    qDeleteAll(restaurants);
    restaurants.clear();
    QJsonArray jsonRestaurants = repo.getRestaurantsByOwner(ownerId);
    for (const QJsonValue &value : jsonRestaurants) {
        QJsonObject obj = value.toObject();
        RestaurantF *restaurant = new RestaurantF(
            obj["id"].toInt(),
            ownerId,
            obj["name"].toString(),
            obj["address"].toString(),
            obj["start_time"].toString(),
            obj["end_time"].toString(),
            nullptr
            );
        restaurants.append(restaurant);
    }
    endResetModel();
}
