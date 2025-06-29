#ifndef MENUF_H
#define MENUF_H

#include <QWidget>
#include <QList>
#include "fooditeam.h"

namespace Ui {
class MenuF;
}

class MenuF : public QWidget
{
    Q_OBJECT

public:
    explicit MenuF(QWidget *parent = nullptr);
    ~MenuF();
    // احتمالا بعدا ی طوری بریم که مثلا برا نمایش بیایم و طبق نوع غذا ها دسته بندی کنیم


private:
    Ui::MenuF *ui;
    QList<FoodIteam> foods;
};

#endif // MENUF_H
