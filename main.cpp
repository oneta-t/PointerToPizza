#include <QApplication>
#include "RestaurantLogin.h"
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // ایجاد برنامه
    RestaurantLogin loginWindow; // پنجره ورود
    MainWindow *mainWindow = nullptr; // پنجره اصلی

    // اتصال سیگنال به باز کردن MainWindow
    QObject::connect(&loginWindow, &RestaurantLogin::loginSuccess, [&loginWindow, &mainWindow](int id) {
        if (!mainWindow) {
            mainWindow = new MainWindow(id); // ایجاد MainWindow
        }
        mainWindow->show(); // نمایش پنجره
        loginWindow.close(); // بستن پنجره ورود
    });

    loginWindow.show(); // نمایش پنجره ورود
    return app.exec(); // اجرای برنامه
}
