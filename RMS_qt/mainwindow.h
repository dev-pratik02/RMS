#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "orders.h"
#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_orders_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase DB_connection;
    orders *ptrorders;
};
#endif // MAINWINDOW_H
