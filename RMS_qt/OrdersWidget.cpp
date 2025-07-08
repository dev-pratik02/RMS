// OrdersWidget.cpp
#include "OrdersWidget.h"


OrdersWidget::OrdersWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Orders");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; font-weight: bold; padding: 10px;");
    mainLayout->addWidget(title);

    QScrollArea *scrollArea = new QScrollArea;
    QWidget *scrollWidget = new QWidget;
    QGridLayout *gridLayout = new QGridLayout(scrollWidget);

    for (int i = 0; i < 10; ++i) {
        QWidget *card = new QWidget;
        card->setFixedSize(200, 120);
        card->setStyleSheet("background-color: #444; color: white; border-radius: 8px; padding: 10px;");

        QVBoxLayout *layout = new QVBoxLayout(card);
        QLabel *idLabel = new QLabel(QString("Order #%1").arg(i + 1));
        QLabel *tableLabel = new QLabel(QString("Table %1").arg((i % 4) + 1));
        QLabel *timeLabel = new QLabel("Time: 12:30 PM");
        QLabel *statusLabel = new QLabel(QString("Status: %1").arg((i % 2 == 0) ? "Pending" : "Completed"));

        layout->addWidget(idLabel);
        layout->addWidget(tableLabel);
        layout->addWidget(timeLabel);
        layout->addWidget(statusLabel);

        int row = i / 3;
        int col = i % 3;
        gridLayout->addWidget(card, row, col);
    }

    scrollWidget->setLayout(gridLayout);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background-color: transparent;");

    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}
