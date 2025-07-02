#ifndef RESTAURANTF_H
#define RESTAURANTF_H

#include <QWidget>
#include <QList>
#include <QTime>
#include "menuf.h"
#include "createfood.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class CreateFood ;



class RestaurantF : public QWidget
{
    Q_OBJECT

public:
    explicit RestaurantF(int restaurantId, const QString& name, const QString& location,const QString& startTime, const QString& endTime, QWidget *parent = nullptr);
    int getRestaurantId() const;
    QString getName() const;
    QString getLocation() const;
    QString getStartTime() const;
    QString getEndTime() const;
    MenuF* getMenuF() const;

private slots:
    void onAddMenuClicked();

private:
    void setupUi();

    int restaurantId;
    QString name;
    QString location;
    QString startTime;
    QString endTime;
    MenuF* menuF;
    QPushButton* addMenuButton;
    CreateFood* createF;
};

#endif // RESTAURANTF_H
