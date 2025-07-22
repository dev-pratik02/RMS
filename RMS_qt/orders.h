#ifndef ORDERS_H
#define ORDERS_H
#include "checkout.h"
#include "edit_order.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QtSql>


namespace Ui {
class orders;
}

class orders : public QMainWindow
{
    Q_OBJECT

public:
    explicit orders(QWidget *parent = nullptr);
    ~orders();

private slots:


    void on_btn_preparing_clicked();

    void on_btn_ready_clicked();

    void on_btn_served_clicked();

    void on_btn_all_clicked();

private:
    Ui::orders *ui;
    checkout *ptrcheckout;
    edit_order *ptredit_order;

    orders *ptrorders;
    QSqlDatabase db;
    QWidget* createOrderCard(const QString &orderId, const QString &table, const QString &time, const QString &status);
    void ordersPageSetup();
    void setActiveButton(QPushButton* activeBtn);
};

#endif // ORDERS_H
