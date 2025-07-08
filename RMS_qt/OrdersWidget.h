#ifndef ORDERSWIDGET_H
#define ORDERSWIDGET_H

#include <QWidget>
#include "orders.h"

class OrdersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersWidget(QWidget *parent = nullptr);

private:
    QWidget* createOrderCard(const QString &orderId, const QString &table, const QString &time, const QString &status);

};

#endif // ORDERSWIDGET_H
