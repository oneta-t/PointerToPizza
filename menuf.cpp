#include "menuf.h"
#include <QLabel>
#include <QJsonArray>
#include <QJsonObject>

MenuF::MenuF(int restaurantId, QWidget *parent)
    : QWidget(parent), restaurantId(restaurantId)
{
    setupUi();
    loadMenu();
}

MenuF::~MenuF()
{
}

void MenuF::setupUi()
{
    QLabel* titleLabel = new QLabel("منوی رستوران", this);
    foodList = new QListWidget(this);
    backButton = new QPushButton("بازگشت", this);
    backButton->setObjectName("BackButton");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(foodList);
    layout->addWidget(backButton);
    layout->addStretch();

    setLayout(layout);

    connect(foodList, &QListWidget::itemDoubleClicked, this, &MenuF::onAddToCartClicked);
    connect(backButton, &QPushButton::clicked, this, &MenuF::hide);
}

void MenuF::loadMenu()
{
    MenuRepository repo;
    QJsonArray menuItems = repo.getMenu(restaurantId);
    foodList->clear();

    for (const QJsonValue& value : menuItems) {
        QJsonObject item = value.toObject();
        QString itemText = QString("%1 - %2 (%3 تومن)")
                               .arg(item["name"].toString())
                               .arg(item["type"].toString())
                               .arg(item["price"].toDouble());
        QListWidgetItem* listItem = new QListWidgetItem(itemText, foodList);
        listItem->setData(Qt::UserRole, item["item_id"].toInt());
    }
}

void MenuF::onAddToCartClicked(QListWidgetItem* item)
{
    int itemId = item->data(Qt::UserRole).toInt();
    // فرضاً Cart یک متد addItem داره
    // Cart* cart = parent()->findChild<Cart*>("Cart");
    // if (cart) cart->addItem(itemId, item->text());
    QMessageBox::information(this, "سبد خرید", QString("غذا با شناسه %1 به سبد خرید اضافه شد.").arg(itemId));
}
