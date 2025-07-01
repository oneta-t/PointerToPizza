QT += core gui widgets
CONFIG += c++11
TARGET = RestaurantLogin
TEMPLATE = app

SOURCES += main.cpp RestaurantLogin.cpp MainWindow.cpp user.cpp customer.cpp restaurantmanager.cpp order.cpp FoodDeliverySystem.cpp admin.cpp fooditeam.cpp menu.cpp restaurant.cpp deliveryperson.cpp realtimeordermanager.cpp orderstatushistory.cpp
HEADERS += RestaurantLogin.h MainWindow.h user.h customer.h restaurantmanager.h order.h FoodDeliverySystem.h admin.h fooditeam.h menu.h restaurant.h deliveryperson.h realtimeordermanager.h orderstatushistory.h restaurantmodel.h restaurantf.h restaurantregistration.h
FORMS += RestaurantLogin.ui MainWindow.ui admin.ui customer.ui restaurantmanager.ui fooditeam.ui menu.ui restaurant.ui
