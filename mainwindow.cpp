#include "MainWindow.h"
#include "ui_mainwindow.h"
//#include "MainWindow.ui"
#include <QMessageBox>
#include <QSqlQuery>

MainWindow::MainWindow(int restaurantId, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), db(QSqlDatabase::addDatabase("QSQLITE")), restaurantId(restaurantId) {
    ui->setupUi(this);

    //connect(ui->viewOrdersButton, &QPushButton::clicked, this, &MainWindow::viewOrders);

    db.setDatabaseName("restaurant.db");
    if (!db.open()) {
        QMessageBox::critical(this, "خطا", "دیتابیس باز نشد!");
    } else {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY AUTOINCREMENT, restaurant_id INTEGER, order_details TEXT)");
        query.exec("INSERT OR IGNORE INTO orders (restaurant_id, order_details) VALUES (1, 'سفارش غذا شماره 1')");
        query.exec("INSERT OR IGNORE INTO orders (restaurant_id, order_details) VALUES (2, 'سفارش غذا شماره 2')");
    }
}

MainWindow::~MainWindow() {
    delete ui;
    db.close();
}

void MainWindow::viewOrders() {
    QSqlQuery query;
    query.prepare("SELECT order_details FROM orders WHERE restaurant_id = :id");
    query.bindValue(":id", restaurantId);
    if (query.exec()) {
        QString orders;
        while (query.next()) {
            orders += query.value(0).toString() + "\n";
        }
        if (orders.isEmpty()) {
            QMessageBox::information(this, "نتیجه", "هیچ سفارشی وجود نداره!");
        } else {
            QMessageBox::information(this, "سفارش‌ها", orders);
        }
    } else {
        QMessageBox::warning(this, "خطا", "نمی‌تونم سفارش‌ها رو بخونم!");
    }
}
