// orders.cpp
#include "orders.h"
#include "ui_orders.h"

orders::orders(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::orders)
{
    ui->setupUi(this);

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
    topGrid->setHorizontalSpacing(4);
    topGrid->setVerticalSpacing(1);

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

    // --- Middle Section: Table of order items (6 rows) ---
    QTableWidget *orderTable = new QTableWidget(6, 3, card);
    orderTable->setHorizontalHeaderLabels(QStringList() << "Name" << "Qty" << "Price");
    orderTable->verticalHeader()->setVisible(false);
    orderTable->horizontalHeader()->setStretchLastSection(false);
    orderTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    orderTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    orderTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    orderTable->setSelectionMode(QAbstractItemView::NoSelection);
    orderTable->setShowGrid(false);
    orderTable->setStyleSheet(
        "QTableWidget { background: #222; color: white; border: none; font-size: 10px; }"
        "QHeaderView::section { background: #444; color: white; border: none; font-size: 10px; }"
    );
    orderTable->setFixedHeight(140);

    // Example data for demonstration (fill up to 6 rows)
    QStringList names = {"Burger", "Fries", "Soda", "Pizza", "Salad", "Coffee"};
    QStringList qtys = {"2", "1", "2", "1", "1", "3"};
    QStringList prices = {"$10", "$3", "$4", "$8", "$5", "$6"};
    for (int i = 0; i < 6; ++i) {
        orderTable->setItem(i, 0, new QTableWidgetItem(names.value(i)));
        orderTable->setItem(i, 1, new QTableWidgetItem(qtys.value(i)));
        orderTable->setItem(i, 2, new QTableWidgetItem(prices.value(i)));
    }

    mainLayout->addWidget(orderTable);

    // --- Bottom Section: Buttons (not connected) ---
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

    return card;
}

orders::~orders()
{
    delete ui;
}


