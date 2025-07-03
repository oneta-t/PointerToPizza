#include "CreateFood.h"
#include <QLabel>

// سازنده با اشاره‌گر به رستوران
CreateFood::CreateFood(RestaurantF* restaurant, QWidget *parent)
    : QWidget(parent), restaurant(restaurant)
{
    setupUi();
}

// دestructor
CreateFood::~CreateFood()
{
}

// تنظیم رابط کاربری
void CreateFood::setupUi()
{
    QLabel* nameLabel = new QLabel("نام غذا:", this);
    nameInput = new QLineEdit(this);
    QLabel* typeLabel = new QLabel("نوع غذا (main_course/dessert/beverage):", this);
    typeInput = new QLineEdit(this);
    QLabel* priceLabel = new QLabel("قیمت:", this);
    priceInput = new QLineEdit(this);
    QLabel* ingredientsLabel = new QLabel("مواد اولیه:", this);
    ingredientsInput = new QLineEdit(this);
    okButton = new QPushButton("تأیید", this);
    okButton->setObjectName("OkButton");
    backButton = new QPushButton("بازگشت", this);
    backButton->setObjectName("BackButton");

    // چیدمان عمودی
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(nameInput);
    layout->addWidget(typeLabel);
    layout->addWidget(typeInput);
    layout->addWidget(priceLabel);
    layout->addWidget(priceInput);
    layout->addWidget(ingredientsLabel);
    layout->addWidget(ingredientsInput);
    layout->addWidget(okButton);
    layout->addWidget(backButton);
    layout->addStretch();

    setLayout(layout);

    // اتصال سیگنال‌ها
    connect(okButton, &QPushButton::clicked, this, &CreateFood::onOkButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &CreateFood::onBackButtonClicked);
}

// تأیید و ذخیره غذا در پایگاه داده
void CreateFood::onOkButtonClicked()
{
    QString name = nameInput->text().trimmed();
    QString type = typeInput->text().trimmed();
    QString priceStr = priceInput->text().trimmed();
    QString ingredients = ingredientsInput->text().trimmed();

    // بررسی خالی نبودن فیلدها
    if (name.isEmpty() || type.isEmpty() || priceStr.isEmpty() || ingredients.isEmpty()) {
        QMessageBox::warning(this, "خطا", "لطفاً همه‌ی فیلدها را پر کنید");
        return;
    }

    // بررسی معتبر بودن قیمت
    bool ok;
    double price = priceStr.toDouble(&ok);
    if (!ok || price <= 0) {
        QMessageBox::warning(this, "خطا", "قیمت باید یک عدد معتبر باشد");
        return;
    }

    // ذخیره غذا در پایگاه داده
    MenuRepository repo;
    if (repo.addMenuItem(restaurant->getRestaurantId(), name, price, type, ingredients)) {
        QMessageBox::information(this, "موفقیت", "غذا با موفقیت به منو اضافه شد.");
        restaurant->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "خطا", "ثبت غذا ناموفق بود.");
    }
}

// بازگشت به صفحه رستوران
void CreateFood::onBackButtonClicked()
{
    restaurant->show();
    this->hide();
}
