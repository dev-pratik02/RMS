#ifndef CHANGE_PASSWORD_H
#define CHANGE_PASSWORD_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include "utils.h"
#include "globals.h"
#include "databasemanager.h"

namespace Ui {
class change_password;
}

class change_password : public QDialog
{
    Q_OBJECT

public:
    explicit change_password(QWidget *parent = nullptr);
    ~change_password();

private slots:
    void on_btn_reset_clicked();

    void on_btn_save_clicked();

private:
    Ui::change_password *ui;
    QSqlDatabase db;
};

#endif // CHANGE_PASSWORD_H
