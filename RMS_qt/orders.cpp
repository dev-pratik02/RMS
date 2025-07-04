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
    // Remove fixed size, use minimum size instead for better layout flexibility
    card->setMinimumSize(200, 120);
    card->setStyleSheet(
        "background-color: #333;"
        "border-radius: 8px;"
        "padding: 10px;"
    );

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(4);

    QLabel *idLabel = new QLabel("Order #" + orderId, card);
    QLabel *tableLabel = new QLabel("Table: " + table, card);
    QLabel *timeLabel = new QLabel("Time: " + time, card);
    QLabel *statusLabel = new QLabel("Status: " + status, card);

    QString labelStyle = "color: white; background: transparent; border: none; font-size: 13px;";
    idLabel->setStyleSheet(labelStyle);
    tableLabel->setStyleSheet(labelStyle);
    timeLabel->setStyleSheet(labelStyle);
    statusLabel->setStyleSheet(labelStyle);

    idLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    tableLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    timeLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    statusLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    // Enable word wrap for all labels
    idLabel->setWordWrap(true);
    tableLabel->setWordWrap(true);
    timeLabel->setWordWrap(true);
    statusLabel->setWordWrap(true);

    layout->addWidget(idLabel);
    layout->addWidget(tableLabel);
    layout->addWidget(timeLabel);
    layout->addWidget(statusLabel);
    layout->addStretch();

    return card;
}

orders::~orders()
{
    delete ui;
}


