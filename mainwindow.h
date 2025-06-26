#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(int restaurantId, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void viewOrders();
   // void QPushButton();
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    int restaurantId;
};

#endif // MAINWINDOW_H
