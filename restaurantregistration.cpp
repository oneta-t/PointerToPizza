#include "restaurantregistration.h"
#include "ui_restaurantregistration.h"
#include "restaurantrepository.h"
#include <QMessageBox>
#include <QTime>
#include <QSqlQuery>

// سازنده کلاس RestaurantRegistration
RestaurantRegistration::RestaurantRegistration(RestaurantManager *RManager, QWidget *parent)
    : QWidget(parent), ui(new Ui::RestaurantRegistration), RManager(RManager)
{
    ui->setupUi(this);
}

RestaurantRegistration::~RestaurantRegistration()
{
    delete ui;
}

// مدیریت کلیک روی دکمه تأیید (OK)
void RestaurantRegistration::on_pushButtonOK_clicked()
{
    QString nameR = ui->name->text().trimmed();
    QString address = ui->address->text().trimmed();
    QString startT = ui->start->text().trimmed();
    QString endT = ui->end->text().trimmed();

    if (nameR.isEmpty() || address.isEmpty() || startT.isEmpty() || endT.isEmpty())
    {
        QMessageBox::warning(this, "خطا", "لطفاً همه‌ی فیلدها را پر کنید");
        return;
    }

    // تبدیل زمان‌ها به فرمت QTime برای بررسی صحت
    QTime startTime = QTime::fromString(startT, "hh:mm");
    QTime endTime = QTime::fromString(endT, "hh:mm");
    if (!startTime.isValid() || !endTime.isValid())
    {
        QMessageBox::warning(this, "خطا", "فرمت زمان باید به شکل hh:mm باشد (مثال: 09:00)");
        return;
    }
    if (endTime <= startTime)
    {
        QMessageBox::warning(this, "خطا", "زمان پایان باید بعد از زمان شروع باشد");
        return;
    }

    // دریافت userId از RestaurantManager
    int ownerId = RManager->getUserId(); /

    // ایجاد نمونه از Repository برای ذخیره رستوران
    RestaurantRepository repo;
    if (repo.addRestaurant(ownerId, nameR, address, startT, endT))
    {
        // دریافت آخرین شناسه رستوران اضافه‌شده
        QSqlQuery query(Database::instance().getConnection());
        query.exec("SELECT last_insert_rowid()");
        int restaurantId = -1;
        if (query.next()) {
            restaurantId = query.value(0).toInt();
        }

        if (restaurantId != -1)
        {
            // ایجاد شیء رستوران با شناسه دریافت‌شده
            RestaurantF *newRestaurant = new RestaurantF(restaurantId, ownerId, nameR, address, startT, endT, nullptr);
            if (RManager->restaurantModel->addRestaurant(newRestaurant))
            {
                QMessageBox::information(this, "موفقیت", "رستوران با موفقیت ثبت شد!");
                RManager->loadRestaurants(); // به‌روزرسانی لیست رستوران‌ها
                RManager->show(); // نمایش صفحه مدیر رستوران
                this->hide(); // پنهان کردن صفحه ثبت رستوران
            }
            else
            {
                QMessageBox::warning(this, "خطا", "ثبت رستوران در مدل ناموفق بود.");
                delete newRestaurant; // آزادسازی حافظه
                repo.updateRestaurantStatus(restaurantId, "rejected"); // رد کردن رستوران در دیتابیس
            }
        }
        else
        {
            QMessageBox::warning(this, "خطا", "شناسه رستوران دریافت نشد.");
        }
    }
    else
    {
        QMessageBox::warning(this, "خطا", "ثبت رستوران در دیتابیس ناموفق بود.");
    }
}

void RestaurantRegistration::on_pushButtonBack_clicked()
{
    this->hide(); // پنهان کردن صفحه ثبت
    RManager->show(); // نمایش صفحه مدیر رستوران
}
