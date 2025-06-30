#include "restaurantmanager.h"
#include "ui_restaurantmanager.h"

RestaurantManager::RestaurantManager(QWidget *parent): QWidget(parent), ui(new Ui::RestaurantManager)
{
    ui->setupUi(this);
    this->Registration = new RestaurantRegistration(this);

    // ایجاد مدل رستوران و اتصال آن به QListView
    restaurantModel = new RestaurantModel(this);
    ui->listViewRestaurants->setModel(restaurantModel); // اتصال مدل به QListView
}

RestaurantManager::~RestaurantManager()
{
    delete ui;
}

int RestaurantManager::NextIdRM=0;

RestaurantManager::RestaurantManager(QString name,QString family,QString passw,QString username,QString phone,QString role):User(name,family,passw,username,phone,role)
{
    IdRM = NextIdRM++;
}

void RestaurantManager::on_AddRestaurant_clicked()
{
    this->hide();
    this->Registration->show();
}

