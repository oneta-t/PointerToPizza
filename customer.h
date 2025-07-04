#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>
#include "user.h"

namespace Ui {
class Customer;
}

class Customer : public QWidget, public User
{
    Q_OBJECT

public:
    explicit Customer(QWidget *parent = nullptr);
    Customer(QString name,QString family,QString passw,QString username,QString phone,QString role);
    int getId() const;
    ~Customer();

private:
    Ui::Customer *ui;
    static int NextId;
    int ID;
};

#endif // CUSTOMER_H
