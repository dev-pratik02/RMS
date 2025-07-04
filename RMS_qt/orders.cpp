// orders.cpp
#include "orders.h"
#include "ui_orders.h"

orders::orders(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::orders)
{
    ui->setupUi(this);
    // Remove these lines, as checkout and edit_order now require arguments
    // ptrcheckout= new checkout();
    // ptredit_order= new edit_order();

    // Remove any widget previously set in the scroll area
    if (QWidget *oldWidget = ui->scrollArea->widget()) {
        if (oldWidget != ui->scrollArea->viewport())
            oldWidget->deleteLater();
    }

    const int columns = 3;
    const int cardWidth = 200;
    const int cardHeight = 120;
    const int hSpacing = 12;
    const int vSpacing = 12;
    const int count = 20;
    int rows = (count + columns - 1) / columns;

    QWidget *dynamicCardContainer = new QWidget;
    QGridLayout *gridLayout = new QGridLayout(dynamicCardContainer);
    gridLayout->setSpacing(vSpacing);
    gridLayout->setHorizontalSpacing(hSpacing);
    gridLayout->setVerticalSpacing(vSpacing);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < count; ++i) {
        int row = i / columns;
        int col = i % columns;
        QWidget *card = createOrderCard(
            QString::number(i+1),
            QString::number((i%4)+1),
            "1:45 PM",
            (i%2==0) ? "Pending" : "Completed"
        );
        gridLayout->addWidget(card, row, col);
    }

    // Set a minimum size for the container so the scroll area works
    dynamicCardContainer->setMinimumSize(
        columns * cardWidth + (columns - 1) * hSpacing,
        rows * cardHeight + (rows - 1) * vSpacing
    );

    ui->scrollArea->setWidget(dynamicCardContainer);
}

QWidget* orders::createOrderCard(const QString &orderId, const QString &table, const QString &time, const QString &status)
{
    QWidget *card = new QWidget;
    card->setMinimumSize(200, 260);
    card->setMaximumSize(220, 280);
    card->setStyleSheet(
        "background-color: #333;"
        "border-radius: 8px;"
        "padding: 4px;"
    );

    QVBoxLayout *mainLayout = new QVBoxLayout(card);
    mainLayout->setContentsMargins(6, 6, 6, 6);
    mainLayout->setSpacing(3);

    // --- Top Section: 2x2 grid for info labels, with reduced spacing ---
    QWidget *topSection = new QWidget(card);
    QGridLayout *topGrid = new QGridLayout(topSection);
    topGrid->setContentsMargins(0, 0, 0, 0);
    topGrid->setHorizontalSpacing(2); // less horizontal space
    topGrid->setVerticalSpacing(0);   // less vertical space

    QString labelStyle = "color: white; background: transparent; border: none; font-size: 10px;";

    QLabel *idLabel = new QLabel("Order #" + orderId, topSection);
    QLabel *timeLabel = new QLabel("Time: " + time, topSection);
    QLabel *tableLabel = new QLabel("Table: " + table, topSection);
    QLabel *statusLabel = new QLabel("Status: " + status, topSection);

    idLabel->setStyleSheet(labelStyle);
    timeLabel->setStyleSheet(labelStyle);
    tableLabel->setStyleSheet(labelStyle);
    statusLabel->setStyleSheet(labelStyle);

    idLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    timeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    tableLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    statusLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    idLabel->setWordWrap(true);
    timeLabel->setWordWrap(true);
    tableLabel->setWordWrap(true);
    statusLabel->setWordWrap(true);

    topGrid->addWidget(idLabel, 0, 0);
    topGrid->addWidget(timeLabel, 0, 1);
    topGrid->addWidget(tableLabel, 1, 0);
    topGrid->addWidget(statusLabel, 1, 1);

    mainLayout->addWidget(topSection);

    // --- Table Header as Labels (aligned with table columns) ---
    QWidget *headerWidget = new QWidget(card);
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(0);

    // Set column widths for both header and table
    int nameColWidth = 90;
    int qtyColWidth = 40;
    int priceColWidth = 50;

    QLabel *nameLabel = new QLabel("Name", headerWidget);
    QLabel *qtyLabel = new QLabel("Qty", headerWidget);
    QLabel *priceLabel = new QLabel("Price", headerWidget);

    nameLabel->setStyleSheet("color: white; background: transparent; font-size: 11px; font-weight: bold; padding: 4px 4px;");
    qtyLabel->setStyleSheet("color: white; background: transparent; font-size: 11px; font-weight: bold; padding: 4px 4px;");
    priceLabel->setStyleSheet("color: white; background: transparent; font-size: 11px; font-weight: bold; padding: 4px 4px;");

    nameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    qtyLabel->setAlignment(Qt::AlignCenter);
    priceLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    nameLabel->setFixedWidth(nameColWidth);
    qtyLabel->setFixedWidth(qtyColWidth);
    priceLabel->setFixedWidth(priceColWidth);

    headerLayout->addWidget(nameLabel);
    headerLayout->addWidget(qtyLabel);
    headerLayout->addWidget(priceLabel);

    mainLayout->addWidget(headerWidget);

    // --- Middle Section: Table of order items (6 rows, no headers) ---
    QTableWidget *orderTable = new QTableWidget(6, 3, card);
    orderTable->horizontalHeader()->setVisible(false);
    orderTable->verticalHeader()->setVisible(false);
    orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    orderTable->setFocusPolicy(Qt::NoFocus);
    orderTable->setSelectionMode(QAbstractItemView::NoSelection);
    orderTable->setShowGrid(false);
    orderTable->setFixedHeight(170);
    orderTable->setStyleSheet(
        "QTableWidget {"
        " background: #222;"
        " color: white;"
        " border: none;"
        " font-size: 13px;"
        "}"
        "QTableWidget::item {"
        " padding: 4px;"
        " background: transparent;"
        "}"
    );
    orderTable->setColumnWidth(0, nameColWidth);
    orderTable->setColumnWidth(1, qtyColWidth);
    orderTable->setColumnWidth(2, priceColWidth);

    // Example data for demonstration (fill up to 6 rows)
    QStringList names, qtys, prices;
    if (orderId == "1") {
        names = {"Burger", "Fries", "Soda", "Pizza", "Salad", "Coffee"};
        qtys = {"2", "1", "2", "1", "1", "3"};
        prices = {"$10", "$3", "$4", "$8", "$5", "$6"};
    } else if (orderId == "2") {
        names = {"Pizza", "Soda", "Fries", "Burger", "Coffee", "Salad"};
        qtys = {"1", "2", "2", "1", "2", "1"};
        prices = {"$8", "$4", "$3", "$10", "$6", "$5"};
    } else if (orderId == "3") {
        names = {"Salad", "Coffee", "Pizza", "Tea", "Burger", "Fries"};
        qtys = {"1", "3", "1", "2", "1", "2"};
        prices = {"$5", "$6", "$8", "$3", "$10", "$3"};
    } else if (orderId == "4") {
        names = {"Sandwich", "Tea", "Fries", "Pizza", "Soda", "Salad"};
        qtys = {"2", "1", "1", "2", "1", "1"};
        prices = {"$7", "$3", "$3", "$8", "$4", "$5"};
    } else {
        // For other cards, generate some variation based on orderId
        int id = orderId.toInt();
        names = {"Burger", "Pizza", "Coffee", "Fries", "Salad", "Soda"};
        qtys = {
            QString::number((id % 3) + 1),
            QString::number((id % 2) + 1),
            QString::number((id % 4) + 1),
            QString::number((id % 2) + 2),
            QString::number((id % 5) + 1),
            QString::number((id % 3) + 2)
        };
        prices = {"$10", "$8", "$6", "$3", "$5", "$4"};
    }
    for (int i = 0; i < 6; ++i) {
        QTableWidgetItem *item0 = new QTableWidgetItem(names.value(i));
        QTableWidgetItem *item1 = new QTableWidgetItem(qtys.value(i));
        QTableWidgetItem *item2 = new QTableWidgetItem(prices.value(i));
        item0->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        orderTable->setItem(i, 0, item0);
        orderTable->setItem(i, 1, item1);
        orderTable->setItem(i, 2, item2);
    }

    mainLayout->addWidget(orderTable);

    // --- Bottom Section: Buttons ---
    QWidget *bottomSection = new QWidget(card);
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomSection);
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    bottomLayout->setSpacing(6);

    QPushButton *editBtn = new QPushButton("Edit", bottomSection);
    QPushButton *checkoutBtn = new QPushButton("Checkout", bottomSection);

    editBtn->setStyleSheet("background-color: #555; color: white; border-radius: 4px; padding: 2px 8px; font-size: 10px;");
    checkoutBtn->setStyleSheet("background-color: #0078d7; color: white; border-radius: 4px; padding: 2px 8px; font-size: 10px;");

    editBtn->setFixedHeight(18);
    checkoutBtn->setFixedHeight(18);

    bottomLayout->addWidget(editBtn);
    bottomLayout->addWidget(checkoutBtn);

    mainLayout->addWidget(bottomSection);

    // Prepare order items for passing (example data)
    QList<QList<QString>> items;
    for (int i = 0; i < 6; ++i) {
        items.append({names.value(i), qtys.value(i), prices.value(i)});
    }

    // --- Connect buttons to open dialogs ---
    connect(editBtn, &QPushButton::clicked, this, [=]() {
        edit_order *dlg = new edit_order(orderId, table, time, status, items, card);
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->show();
    });
    connect(checkoutBtn, &QPushButton::clicked, this, [=]() {
        checkout *dlg = new checkout(orderId, table, time, status, items, card);
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->show();
    });

    return card;
}

orders::~orders()
{
    delete ui;
}








