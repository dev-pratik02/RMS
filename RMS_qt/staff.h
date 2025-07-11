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

private:
    Ui::staff *ui;
    addstaff *ptraddstaff;
    QSqlDatabase mydb;
};

#endif // STAFF_H
