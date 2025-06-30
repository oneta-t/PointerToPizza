#ifndef CREATEFOOD_H
#define CREATEFOOD_H

#include <QWidget>

namespace Ui {
class CreateFood;
}

class CreateFood : public QWidget
{
    Q_OBJECT

public:
    explicit CreateFood(QWidget *parent = nullptr);
    ~CreateFood();

private:
    Ui::CreateFood *ui;
};

#endif // CREATEFOOD_H
