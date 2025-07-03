#ifndef CREATEFOOD_H
#define CREATEFOOD_H

#include "restaurantf.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include "restaurantF.h"
#include "menuRepository.h"

// کلاس فرم افزودن غذای جدید
class CreateFood : public QWidget
{
    Q_OBJECT

public:
    // سازنده با اشاره‌گر به رستوران
    explicit CreateFood(RestaurantF* restaurant, QWidget *parent = nullptr);
    // دestructor
    ~CreateFood();

private slots:
    // تأیید و ذخیره غذا
    void onOkButtonClicked();
    // بازگشت به صفحه رستوران
    void onBackButtonClicked();

private:
    // تنظیم رابط کاربری
    void setupUi();

    RestaurantF* restaurant; // اشاره‌گر به رستوران
    QLineEdit* nameInput; // فیلد نام غذا
    QLineEdit* typeInput; // فیلد نوع غذا
    QLineEdit* priceInput; // فیلد قیمت
    QLineEdit* ingredientsInput; // فیلد مواد اولیه
    QPushButton* okButton; // دکمه تأیید
    QPushButton* backButton; // دکمه بازگشت
};

#endif // CREATEFOOD_H
