#ifndef FOODITEAM_H
#define FOODITEAM_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class FoodIteam : public QWidget
{
    Q_OBJECT

public:
    explicit FoodIteam(int itemId, const QString& foodName, const QString& ingredients,
                       const QString& type, float price, QWidget *parent = nullptr);
    int getItemId() const;
    QString getFoodName() const;
    QString getIngredients() const;
    QString getType() const;
    float getPrice() const;

private:
    void setupUi();

    int itemId;
    QString foodName;
    QString ingredients;
    QString type;
    float price;
};

#endif // FOODITEAM_H
