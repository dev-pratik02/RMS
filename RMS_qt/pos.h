#ifndef POS_H
#define POS_H

#include <QMainWindow>
#include <QtSql>
#include "pos_addorder.h"

namespace Ui {
class pos;
}

class POS_AddOrder;

class pos : public QMainWindow
{
    Q_OBJECT

public:
    explicit pos(QWidget *parent = nullptr);
    ~pos();

private slots:
    void on_btn_place_order_clicked();

private:
    Ui::pos *ui;
    QSqlDatabase mydb;
    POS_AddOrder *ptraddorder;
};

#endif // POS_H
