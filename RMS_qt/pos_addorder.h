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
    int id;           // menu_item_id
    int quantity;
    double price;
};

class POS_AddOrder : public QWidget
{
    Q_OBJECT

public:
    explicit POS_AddOrder(QString table_no, QWidget *parent = nullptr);
    ~POS_AddOrder();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void addItemToOrder();
    void decreaseItemQuantity();
    void sendOrder();


private:
    Ui::POS_AddOrder *ui;

    // Layouts and widgets
    QGridLayout *itemsLayout;
    QLabel *orderInfoLabel;
    QTableWidget *orderTable;
    QLabel *subtotalLabel;
    QLabel *serviceChargeLabel;
    QLabel *totalLabel;
    QPushButton *resetButton;
    QPushButton *saveButton;

    // Data
    QSqlDatabase db;
    QString m_tableNo;
    QString m_orderId;
    QMap<QString, OrderItem> orderItems;

    // Logic
    void updateOrderTable();
    void loadItemsForCategory(const QString &category);
};

#endif // POS_ADDORDER_H
