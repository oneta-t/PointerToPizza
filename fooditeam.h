#ifndef FOODITEAM_H
#define FOODITEAM_H

#include <QWidget>

    namespace Ui {
    class FoodIteam;
}

// کلاس FoodIteam برای نمایش اطلاعات غذا
class FoodIteam : public QWidget
{
    Q_OBJECT

public:
    // سازنده با اطلاعات غذا
    explicit FoodIteam(int id, int restaurantId, QString foodName, QString ingredients, QString type, float price, QWidget *parent = nullptr);
    ~FoodIteam();

    int getId() const;
    int getRestaurantId() const;
    QString getFoodName() const;
    QString getIngredients() const;
    QString getType() const;
    float getPrice() const;

private:
    Ui::FoodIteam *ui;
    int id;
    int restaurantId;
    QString foodName;
    QString ingredients;
    QString type;
    float price;
    //برای سفارش هم باید باشه چیزی
};

#endif // FOODITEAM_H
