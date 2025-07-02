#include "restaurantRegistration.h"
#include <QLabel>

RestaurantRegistration::RestaurantRegistration(RestaurantManager* rManager, QWidget *parent)
    : QWidget(parent), rManager(rManager)
{
    setupUi();
}

RestaurantRegistration::~RestaurantRegistration()
{
    // همه ویجت‌ها توسط Qt مدیریت می‌شوند
}

void RestaurantRegistration::setupUi()
{
    // ایجاد ویجت‌ها
    QLabel* nameLabel = new QLabel("نام رستوران:", this);
    nameInput = new QLineEdit(this);
    QLabel* locationLabel = new QLabel("آدرس:", this);
    locationInput = new QLineEdit(this);
    QLabel* startTimeLabel = new QLabel("ساعت شروع:", this);
    startTimeInput = new QLineEdit(this);
    startTimeInput->setPlaceholderText("HH:MM");
    QLabel* endTimeLabel = new QLabel("ساعت پایان:", this);
    endTimeInput = new QLineEdit(this);
    endTimeInput->setPlaceholderText("HH:MM");
    okButton = new QPushButton("تأیید", this);
    okButton->setObjectName("OkButton");
    backButton = new QPushButton("بازگشت", this);
    backButton->setObjectName("BackButton");

    // تنظیم چیدمان عمودی
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(nameInput);
    layout->addWidget(locationLabel);
    layout->addWidget(locationInput);
    layout->addWidget(startTimeLabel);
    layout->addWidget(startTimeInput);
    layout->addWidget(endTimeLabel);
    layout->addWidget(endTimeInput);
    layout->addWidget(okButton);
    layout->addWidget(backButton);
    layout->addStretch();

    setLayout(layout);

    // اتصال سیگنال‌ها به اسلات‌ها
    connect(okButton, &QPushButton::clicked, this, &RestaurantRegistration::onOkButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &RestaurantRegistration::onBackButtonClicked);
}

void RestaurantRegistration::onOkButtonClicked()
{
    QString name = nameInput->text().trimmed();
    QString location = locationInput->text().trimmed();
    QString startTime = startTimeInput->text().trimmed();
    QString endTime = endTimeInput->text().trimmed();

    if (name.isEmpty() || location.isEmpty() || startTime.isEmpty() || endTime.isEmpty()) {
        QMessageBox::warning(this, "خطا", "لطفاً همه‌ی فیلدها را پر کنید");
        return;
    }

    // اعتبارسنجی فرمت زمان (اختیاری، می‌توانید قوانین سخت‌گیرانه‌تری اضافه کنید)
    QRegExp timeRegex("\\d{2}:\\d{2}");
    if (!timeRegex.exactMatch(startTime) || !timeRegex.exactMatch(endTime)) {
        QMessageBox::warning(this, "خطا", "فرمت ساعت باید HH:MM باشد");
        return;
    }

    // ذخیره رستوران در پایگاه داده
    RestaurantRepository repo;
    if (repo.addRestaurant(rManager->getUserId(), name, location, startTime, endTime)) {
        // ایجاد شیء رستوران جدید
        RestaurantF* newRestaurant = new RestaurantF(0, name, location, startTime, endTime, this);
        rManager->restaurantModel->addRestaurant(newRestaurant);

        QMessageBox::information(this, "موفقیت", "رستوران با موفقیت ثبت شد.");
        rManager->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "خطا", "ثبت رستوران ناموفق بود.");
    }
}

void RestaurantRegistration::onBackButtonClicked()
{
    rManager->show();
    this->hide();
}

