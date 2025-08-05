#ifndef USERS_H
#define USERS_H

#include <QDialog>
#include <QtSql>
#include "databasemanager.h"
#include "signup.h"

namespace Ui {
class users;
}

class users : public QDialog
{
    Q_OBJECT

public:
    explicit users(QWidget *parent = nullptr);
    ~users();

private slots:
    void on_btn_adduser_clicked();

private:
    Ui::users *ui;
    QSqlDatabase db;
    signup *ptrsignup;
};

#endif // USERS_H
