#ifndef FOODITEAM_H
#define FOODITEAM_H

#include <QWidget>

namespace Ui {
class FoodIteam;
}

class FoodIteam : public QWidget
{
    Q_OBJECT

public:
    explicit FoodIteam(QWidget *parent = nullptr);
    FoodIteam(QString foodName,QString ingredients,QString type,float price);
    QString getFoodName() const;
    QString getIngredients()const;
    QString getType() const;
    float getPrice() const;
    ~FoodIteam();

private:
    Ui::FoodIteam *ui;
    static int NextIdF;
    int IdF;
    QString FoodName;
    QString Type;
    QString Ingredients;
    float Price;

};

#endif // FOODITEAM_H
