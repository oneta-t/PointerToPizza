#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "User.h"
#include "UserInformationPage.h"
#include "Cart.h"

class Customer : public QWidget, public User
{
    Q_OBJECT

public:
    explicit Customer(int userId, QWidget *parent = nullptr);
    Customer(int userId, const QString& name, const QString& family, const QString& passw,
             const QString& username, const QString& phone, const QString& role);
    int getUserId() const;
    ~Customer();

private slots:
    void onUserInfoButtonClicked();

private:
    void setupUi();

    int userId;
    QPushButton* userInfoButton;
    UserInformationPage* infPage;
    Cart* cart;
};

#endif // CUSTOMER_H
