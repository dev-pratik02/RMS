// orders.cpp
#include "orders.h"
#include "ui_orders.h"

orders::orders(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::orders)
{
    ui->setupUi(this);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *container = new QWidget;
    QGridLayout *gridLayout = new QGridLayout(container);
    gridLayout->setSpacing(12);

    const int columns = 3; // Number of cards per row

    for (int i = 0; i < 20; ++i) {
        int row = i / columns;
        int col = i % columns;

        QWidget *card = createOrderCard(QString::number(i+1), "Table 2", "1:45 PM", "Pending");
        gridLayout->addWidget(card, row, col);
    }

    container->setLayout(gridLayout);
    scrollArea->setWidget(container);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(scrollArea);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}

QWidget* orders::createOrderCard(const QString &orderId, const QString &table, const QString &time, const QString &status)
{
    QWidget *card = new QWidget;
    card->setFixedSize(200, 120);
    card->setStyleSheet("background-color: #333; color: white; border-radius: 8px; padding: 10px;");

    QVBoxLayout *layout = new QVBoxLayout(card);
    QLabel *idLabel = new QLabel(orderId);
    QLabel *tableLabel = new QLabel("Table: " + table);
    QLabel *timeLabel = new QLabel("Time: " + time);
    QLabel *statusLabel = new QLabel("Status: " + status);

    layout->addWidget(idLabel);
    layout->addWidget(tableLabel);
    layout->addWidget(timeLabel);
    layout->addWidget(statusLabel);

    return card;
}

orders::~orders()
{
    delete ui;
}
