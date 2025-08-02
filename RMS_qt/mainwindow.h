#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "orders.h"
#include "pos.h"
#include "menu.h"
#include "staff.h"
#include "table.h"
#include "profile.h"
#include <QMainWindow>
#include <QtSql>
#include <QPixmap>

class profile;
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


    void on_btn_menu_clicked();

    void on_btn_staff_clicked();

    void on_btn_tables_clicked();

    void on_btn_orders_clicked();

    void on_btn_pos_clicked();

    void on_btn_profile_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase DB_connection;
    QString userRole;
    orders *ptrorders = nullptr;
    class pos *ptrpos = nullptr;
    menu *ptrmenu = nullptr;
    staff *ptrstaff = nullptr;
    table *ptrtables = nullptr;
    profile *ptrprofile = nullptr;
};
#endif // MAINWINDOW_H
