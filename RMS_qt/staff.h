#ifndef STAFF_H
#define STAFF_H

#include <QMainWindow>
#include <QtSql>
#include "addstaff.h"

namespace Ui {
class staff;
}

class staff : public QMainWindow
{
    Q_OBJECT

public:
    explicit staff(QWidget *parent = nullptr);
    ~staff();

private slots:
    void on_ADDSTAFF_clicked();
    void loadStaffData();

    void on_btn_staff_access_clicked();

private:
    Ui::staff *ui;
    addstaff *ptraddstaff;
    QSqlDatabase db;
};

#endif // STAFF_H
