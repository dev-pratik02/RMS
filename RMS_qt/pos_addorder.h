#ifndef POS_ADDORDER_H
#define POS_ADDORDER_H
#include "pos.h"
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
#include <QMessageBox>
#include <QInputDialog>


class MainWindow; // Forward declaration
class pos;


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
    explicit POS_AddOrder(QString table_no, class pos *posWindow = nullptr, MainWindow *mainWindow = nullptr, QWidget *parent = nullptr);
    ~POS_AddOrder();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void addItemToOrder();
    void decreaseItemQuantity();
    void sendOrder();
    void onAddNotesClicked();


private:
    Ui::POS_AddOrder *ui;
    class pos *m_posWindow = nullptr;
    MainWindow *m_mainWindow = nullptr;


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
    QString notes;  // To store the notes text

    // Logic
    void updateOrderTable();
    void loadItemsForCategory(const QString &category);
    void loadExistingOrderItems(const QString &orderId);
};

#endif // POS_ADDORDER_H
