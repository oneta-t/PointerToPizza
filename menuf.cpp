#include "menuf.h"
#include "ui_menuf.h"
#include "menurepository.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QInputDialog>

MenuF::MenuF(int restaurantId, QWidget *parent) : QWidget(parent), ui(new Ui::MenuF), restaurantId(restaurantId)
{
    ui->setupUi(this);
    loadMenu(); // لود منو در ابتدا

    // اتصال اسلات‌ها به دکمه‌ها
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &MenuF::on_pushButtonAdd_clicked);
    connect(ui->pushButtonEdit, &QPushButton::clicked, this, &MenuF::on_pushButtonEdit_clicked);
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, &MenuF::on_pushButtonDelete_clicked);
}

// دستراکتور برای آزادسازی منابع
MenuF::~MenuF()
{
    qDeleteAll(foodItems); // آزادسازی همه آیتم‌ها
    delete ui;
}

// افزودن آیتم به منو
void MenuF::addFoodItem(FoodIteam* foodItem)
{
    if (foodItem) {
        foodItems.append(foodItem);
        updateMenuDisplay(); // به‌روزرسانی نمایش
    }
}

// لود منو از دیتابیس
void MenuF::loadMenu()
{
    qDeleteAll(foodItems); // پاک کردن آیتم‌های قدیمی
    foodItems.clear();
    QJsonArray menu = menuRepo.getMenu(restaurantId);
    for (const QJsonValue &value : menu) {
        QJsonObject obj = value.toObject();
        FoodIteam *food = new FoodIteam(
            obj["item_id"].toInt(),
            restaurantId,
            obj["name"].toString(),
            "", // ingredients فعلاً خالی
            obj["type"].toString(),
            obj["price"].toDouble(),
            this
            );
        foodItems.append(food);
    }
    updateMenuDisplay();
}

// به‌روزرسانی نمایش منو
void MenuF::updateMenuDisplay()
{
    ui->listViewMenu->clear(); // فرض می‌کنیم listViewMenu برای نمایش استفاده می‌شه
    for (FoodIteam *item : foodItems) {
        ui->listViewMenu->addItem(QString("%1 - %2 (قیمت: %3)").arg(item->getFoodName(), item->getType(), QString::number(item->getPrice())));
    }
}

// اسلات برای افزودن آیتم
void MenuF::on_pushButtonAdd_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "اضافه کردن غذا", "نام غذا:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    QString type = QInputDialog::getItem(this, "نوع غذا", "نوع:", QStringList() << "main_course" << "dessert" << "beverage", 0, false, &ok);
    if (!ok || type.isEmpty()) return;

    double price = QInputDialog::getDouble(this, "قیمت غذا", "قیمت:", 0, 0, 1000, 2, &ok);
    if (!ok || price <= 0) return;

    if (menuRepo.addMenuItem(restaurantId, name, price, type)) {
        QMessageBox::information(this, "موفقیت", "غذا با موفقیت اضافه شد!");
        loadMenu(); // لود مجدد منو
    } else {
        QMessageBox::warning(this, "خطا", "اضافه کردن غذا ناموفق بود.");
    }
}

// اسلات برای ویرایش آیتم
void MenuF::on_pushButtonEdit_clicked()
{
    QModelIndex index = ui->listViewMenu->currentIndex();
    if (!index.isValid() || foodItems.isEmpty()) {
        QMessageBox::warning(this, "خطا", "لطفاً یک آیتم را انتخاب کنید.");
        return;
    }

    int itemIndex = index.row();
    FoodIteam *item = foodItems[itemIndex];
    bool ok;
    QString name = QInputDialog::getText(this, "ویرایش غذا", "نام غذا:", QLineEdit::Normal, item->getFoodName(), &ok);
    if (!ok || name.isEmpty()) return;

    QString type = QInputDialog::getItem(this, "نوع غذا", "نوع:", QStringList() << "main_course" << "dessert" << "beverage", 0, false, &ok);
    if (!ok || type.isEmpty()) return;

    double price = QInputDialog::getDouble(this, "قیمت غذا", "قیمت:", item->getPrice(), 0, 1000, 2, &ok);
    if (!ok || price <= 0) return;

    if (menuRepo.editMenuItem(item->getId(), restaurantId, name, price, type)) {
        QMessageBox::information(this, "موفقیت", "غذا با موفقیت ویرایش شد!");
        loadMenu(); // لود مجدد منو
    } else {
        QMessageBox::warning(this, "خطا", "ویرایش غذا ناموفق بود.");
    }
}

// اسلات برای حذف آیتم
void MenuF::on_pushButtonDelete_clicked()
{
    QModelIndex index = ui->listViewMenu->currentIndex();
    if (!index.isValid() || foodItems.isEmpty()) {
        QMessageBox::warning(this, "خطا", "لطفاً یک آیتم را انتخاب کنید.");
        return;
    }

    int itemIndex = index.row();
    FoodIteam *item = foodItems[itemIndex];
    if (QMessageBox::question(this, "تأیید حذف", "آیا مطمئن هستید که می‌خواهید این غذا را حذف کنید؟") == QMessageBox::Yes) {
        if (menuRepo.deleteMenuItem(item->getId(), restaurantId)) {
            QMessageBox::information(this, "موفقیت", "غذا با موفقیت حذف شد!");
            loadMenu(); // لود مجدد منو
        } else {
            QMessageBox::warning(this, "خطا", "حذف غذا ناموفق بود.");
        }
    }
}
