#ifndef MENUF_H
#define MENUF_H

#include <QWidget>
#include <QList>
#include "fooditeam.h"
#include "menurepository.h"

    namespace Ui {
    class MenuF;
}

// کلاس MenuF برای مدیریت منوی رستوران
class MenuF : public QWidget
{
    Q_OBJECT

public:
    // سازنده با اطلاعات منو
    explicit MenuF(int restaurantId, QWidget *parent = nullptr);
    ~MenuF();

    void addFoodItem(FoodIteam* foodItem); // افزودن آیتم به منو
    void loadMenu();                       // لود منو از دیتابیس
    void updateMenuDisplay();              // به‌روزرسانی نمایش منو

private slots:
    void on_pushButtonAdd_clicked();       // اسلات برای افزودن آیتم
    void on_pushButtonEdit_clicked();      // اسلات برای ویرایش آیتم
    void on_pushButtonDelete_clicked();    // اسلات برای حذف آیتم

private:
    Ui::MenuF *ui;
    QList<FoodIteam*> foodItems;
    int restaurantId;
    MenuRepository menuRepo;
};

#endif // MENUF_H
