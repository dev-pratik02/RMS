#ifndef PROFILE_H
#define PROFILE_H
#include "globals.h"
#include "databasemanager.h"
#include "login_page.h"
#include "utils.h"
#include "change_password.h"
#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include "mainwindow.h"

class MainWindow;
namespace Ui {
class profile;
}

class profile : public QDialog
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr, MainWindow *mainWindow=nullptr);
    ~profile();

private slots:
    void on_logout_btn_clicked();

    void on_pass_btn_clicked();

    void on_btn_reset_clicked();

    void on_btn_save_clicked();

private:
    Ui::profile *ui;
    MainWindow *m_mainWindow;
    QSqlDatabase db;
    void load_data();

    change_password *passPage=nullptr;
};

#endif // PROFILE_H
