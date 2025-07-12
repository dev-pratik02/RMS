#ifndef POS_ADDORDER_H
#define POS_ADDORDER_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QMap>
#include <QtSql>
#include <QButtonGroup>
#include <QHeaderView>

namespace Ui {
class POS_AddOrder;
}

class POS_AddOrder : public QWidget
{
    Q_OBJECT

public:
    explicit POS_AddOrder(QWidget *parent = nullptr);
    explicit POS_AddOrder(QString table_no,QWidget *parent = nullptr);

    ~POS_AddOrder();

private slots:
    void addItemToOrder();

private:
    Ui::POS_AddOrder *ui;

    // Left section
    QVBoxLayout *categoryLayout;
    QGridLayout *itemsLayout;

    // Right section
    QLabel *orderInfoLabel;
    QTableWidget *orderTable;
    QPushButton *resetButton;
    QPushButton *saveButton;

    QMap<QString, int> orderItems;
    void updateOrderTable();
    QSqlDatabase db;
};

#endif // POS_ADDORDER_H
