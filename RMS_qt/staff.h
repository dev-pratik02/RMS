#ifndef STAFF_H
#define STAFF_H
#include "addstaff.h"
#include <QMainWindow>

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
};

#endif // STAFF_H
