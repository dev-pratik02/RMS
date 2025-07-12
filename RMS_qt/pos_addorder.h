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
#include <QPixmap>

namespace Ui {
class POS_AddOrder;
}

struct OrderItem {
    int quantity = 0;
    double price = 0.0;
};

class POS_AddOrder : public QWidget
{
    Q_OBJECT

public:
    explicit POS_AddOrder(QString table_no,QWidget *parent = nullptr);

    ~POS_AddOrder();

private slots:
    void addItemToOrder();
    void decreaseItemQuantity();


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
    void updateOrderTable();
    QSqlDatabase db;

    void loadItemsForCategory(const QString &category);
    bool eventFilter(QObject *watched, QEvent *event) override;

    QMap<QString, OrderItem> orderItems;


};

#endif // POS_ADDORDER_H
