#ifndef RESTAURANTREGISTRATION_H
#define RESTAURANTREGISTRATION_H

#include <QWidget>
#include <QMessageBox>
#include "restaurantf.h"
#include "restaurantmanager.h"
#include "restaurantmodel.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include "RestaurantManager.h"
#include "RestaurantRepository.h"

class RestaurantRegistration : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantRegistration(RestaurantManager* rManager, QWidget *parent = nullptr);
    ~RestaurantRegistration();

private slots:
    void onOkButtonClicked();
    void onBackButtonClicked();

private:
    void setupUi();

    RestaurantManager* rManager;
    QLineEdit* nameInput;
    QLineEdit* locationInput;
    QLineEdit* startTimeInput;
    QLineEdit* endTimeInput;
    QPushButton* okButton;
    QPushButton* backButton;
};

#endif // RESTAURANTREGISTRATION_H
