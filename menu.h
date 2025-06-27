#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QList>
#include "fooditeam.h"

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    Menu();
    ~Menu();
    // احتمالا بعدا ی طوری بریم که مثلا برا نمایش بیایم و طبق نوع غذا ها دسته بندی کنیم

private:
    Ui::Menu *ui;
    QList<FoodIteam> foods;
};

#endif // MENU_H
