```cpp
#ifndef RESTAURANTREGISTRATION_H
#define RESTAURANTREGISTRATION_H

#include <QWidget>
#include <QMessageBox>
#include "restaurantf.h"
#include "restaurantmanager.h"
#include "restaurantmodel.h"

    class RestaurantManager;

namespace Ui {
class RestaurantRegistration;
}

class RestaurantRegistration : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantRegistration(RestaurantManager *RManager, QWidget *parent = nullptr);
    ~RestaurantRegistration();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonBack_clicked();

private:
    Ui::RestaurantRegistration *ui;
    RestaurantManager *RManager;
};

#endif // RESTAURANTREGISTRATION_H
```
