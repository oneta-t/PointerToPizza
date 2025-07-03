#ifndef MENUF_H
#define MENUF_H

#include <QWidget>
#include <QList>
#include "fooditeam.h"
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "MenuRepository.h"

class MenuF : public QWidget
{
    Q_OBJECT

public:
    explicit MenuF(int restaurantId, QWidget *parent = nullptr);
    ~MenuF();
    void loadMenu();

private slots:
    void onAddToCartClicked(QListWidgetItem* item);

private:
    void setupUi();

    int restaurantId;
    QListWidget* foodList;
    QPushButton* backButton;
};

#endif // MENUF_H
