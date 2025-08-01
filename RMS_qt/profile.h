#ifndef PROFILE_H
#define PROFILE_H
#include "globals.h"
#include "databasemanager.h"
#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class profile;
}

class profile : public QDialog
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();

private slots:
    void on_logout_btn_clicked();

    void on_pass_btn_clicked();

    void on_btn_reset_clicked();

    void on_btn_save_clicked();

private:
    Ui::profile *ui;
    QSqlDatabase db;
};

#endif // PROFILE_H
