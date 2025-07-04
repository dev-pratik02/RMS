#ifndef ORDERS_H
#define ORDERS_H

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

namespace Ui {
class orders;
}

class orders : public QMainWindow
{
    Q_OBJECT

public:
    explicit orders(QWidget *parent = nullptr);
    ~orders();

private:
    Ui::orders *ui;

    QWidget* createOrderCard(const QString &orderId, const QString &table, const QString &time, const QString &status);
};

#endif // ORDERS_H
