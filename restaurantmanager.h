#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "User.h"
#include "RestaurantModel.h"
#include "RestaurantRegistration.h"

class RestaurantManager : public QWidget, public User
{
    Q_OBJECT

public:
    explicit RestaurantManager(int userId, QWidget *parent = nullptr);
    RestaurantManager(int userId, const QString& name, const QString& family, const QString& passw,
                      const QString& username, const QString& phone, const QString& role);
    int getUserId() const;
    ~RestaurantManager();

private slots:
    void onAddRestaurantClicked();

private:
    void setupUi();

    int userId;
    QPushButton* addRestaurantButton;
    RestaurantModel* restaurantModel;
    RestaurantRegistration* registration;
};

#endif // RESTAURANTMANAGER_H
