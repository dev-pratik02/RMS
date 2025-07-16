#include "checkout.h"
#include "ui_checkout.h"

#include "databasemanager.h"

checkout::checkout(const QString &orderId, const QString &table, const QString &time, const QString &status,
                   const QList<QList<QString>> &items, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::checkout)
{
    ui->setupUi(this);

    // Remove any layout from the frame if present
    QLayout *oldLayout = ui->frame ? ui->frame->layout() : nullptr;
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // --- Card Layout (like edit_order, but table not editable) ---
    QWidget *card = new QWidget(ui->frame);
    // Set the card's layout and spacing so everything fits well
    QVBoxLayout *mainLayout = new QVBoxLayout(card);
    mainLayout->setContentsMargins(12, 12, 12, 12); // tighter margins
    mainLayout->setSpacing(6); // less vertical spacing

    card->setLayout(mainLayout);
    card->setStyleSheet(
        "background-color: #333;"
        "border-radius: 12px;"
        "padding: 0px;"
    );

    // --- Top Section ---
    QWidget *topSection = new QWidget(card);
    QGridLayout *topGrid = new QGridLayout(topSection);
    topGrid->setContentsMargins(0, 0, 0, 0);
    topGrid->setHorizontalSpacing(2);
    topGrid->setVerticalSpacing(0);

    // Give extra height to the first section
    topSection->setMinimumHeight(60);

    // Larger font for order details
    QString labelStyle = "color: white; background: transparent; border: none; font-size: 18px; font-weight: bold;";

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

    topGrid->addWidget(idLabel, 0, 0);
    topGrid->addWidget(timeLabel, 0, 1);
    topGrid->addWidget(tableLabel, 1, 0);
    topGrid->addWidget(statusLabel, 1, 1);

    mainLayout->addWidget(topSection);

    // --- Table Header as Labels ---
    QWidget *headerWidget = new QWidget(card);
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(0);

    int nameColWidth = 200;
    int qtyColWidth = 170;
    int priceColWidth = 80;
    int nameQtyGap = 200;
    int qtyPriceGap=100;

    QLabel *nameLabel = new QLabel("Name", headerWidget);
    QLabel *qtyLabel = new QLabel("Quantity", headerWidget);
    QLabel *priceLabel = new QLabel("Price", headerWidget);

    nameLabel->setStyleSheet("color: white; background: transparent; font-size: 16px; font-weight: bold; padding: 6px 8px;");
    qtyLabel->setStyleSheet("color: white; background: transparent; font-size: 16px; font-weight: bold; padding: 6px 8px;");
    priceLabel->setStyleSheet("color: white; background: transparent; font-size: 16px; font-weight: bold; padding: 6px 8px;");

    nameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    qtyLabel->setAlignment(Qt::AlignRight);
    priceLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    nameLabel->setFixedWidth(nameColWidth);
    qtyLabel->setFixedWidth(qtyColWidth);
    priceLabel->setFixedWidth(priceColWidth);

    headerLayout->addWidget(nameLabel);
    headerLayout->addSpacing(nameQtyGap);
    headerLayout->addWidget(qtyLabel);
    headerLayout->addSpacing(qtyPriceGap);
    headerLayout->addWidget(priceLabel);

    mainLayout->addWidget(headerWidget);

    // --- Order Table (no headers, not editable) ---
    QTableWidget *orderTable = new QTableWidget(items.size(), 3, card);
    orderTable->horizontalHeader()->setVisible(false);
    orderTable->verticalHeader()->setVisible(false);
    orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    orderTable->setFocusPolicy(Qt::NoFocus);
    orderTable->setSelectionMode(QAbstractItemView::NoSelection);
    orderTable->setShowGrid(false); // no row grid lines
    orderTable->setStyleSheet(
        "QTableWidget {"
        " background-color: #333;"
        " color: white;"
        " border: 2px solid #555;"
        " border-radius: 8px;"
        " font-size: 15px;"
        "}"
        "QTableWidget::item {"
        " padding: 6px;"
        " background: transparent;"
        " border: none;"
        "}"
    );
    orderTable->setMinimumHeight(180); // decreased table height
    orderTable->setColumnWidth(0, nameColWidth + nameQtyGap);
    orderTable->setColumnWidth(1, qtyColWidth + qtyPriceGap);
    orderTable->setColumnWidth(2, priceColWidth);

    for (int i = 0; i < items.size(); ++i) {
        QTableWidgetItem *nameItem = new QTableWidgetItem(items[i].value(0));
        QTableWidgetItem *qtyItem = new QTableWidgetItem(items[i].value(1));
        QTableWidgetItem *priceItem = new QTableWidgetItem(items[i].value(2));
        nameItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        qtyItem->setTextAlignment(Qt::AlignCenter);
        priceItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        orderTable->setItem(i, 0, nameItem);
        orderTable->setItem(i, 1, qtyItem);
        orderTable->setItem(i, 2, priceItem);
    }

    mainLayout->addWidget(orderTable);

    // --- Details Section (like first section, after table) ---
    QWidget *detailsSection = new QWidget(card);
    QGridLayout *detailsGrid = new QGridLayout(detailsSection);
    detailsGrid->setContentsMargins(0, 0, 0, 0);
    detailsGrid->setHorizontalSpacing(2);
    detailsGrid->setVerticalSpacing(0);

    // Give extra height to the details section
    detailsSection->setMinimumHeight(60);

    // Calculate subtotal, service charge, total
    double subtotal = 0.0;
    for (int i = 0; i < orderTable->rowCount(); ++i) {
        QString priceStr = orderTable->item(i, 2) ? orderTable->item(i, 2)->text() : QString();
        bool ok = false;
        double price = priceStr.remove(QRegularExpression("[^\\d\\.]")).toDouble(&ok);
        if (ok)
            subtotal += price;
    }
    double serviceCharge = subtotal * 0.10;
    double total = subtotal + serviceCharge;

    QString smallLabelStyle = "color: #bbb; background: transparent; border: none; font-size: 11px; font-weight: bold;";
    QString bigLabelStyle = "color: #fff; background: transparent; border: none; font-size: 16px; font-weight: bold;";

    QLabel *subtotalLabel = new QLabel("Subtotal:", detailsSection);
    QLabel *subtotalValue = new QLabel(QString("$%1").arg(QString::number(subtotal, 'f', 2)), detailsSection);
    QLabel *serviceLabel = new QLabel("Service Charge (10%):", detailsSection);
    QLabel *serviceValue = new QLabel(QString("$%1").arg(QString::number(serviceCharge, 'f', 2)), detailsSection);
    QLabel *totalLabel = new QLabel("Total:", detailsSection);
    QLabel *totalValue = new QLabel(QString("$%1").arg(QString::number(total, 'f', 2)), detailsSection);

    subtotalLabel->setStyleSheet(smallLabelStyle);
    subtotalValue->setStyleSheet(smallLabelStyle);
    serviceLabel->setStyleSheet(smallLabelStyle);
    serviceValue->setStyleSheet(smallLabelStyle);
    totalLabel->setStyleSheet(bigLabelStyle);
    totalValue->setStyleSheet(bigLabelStyle);

    subtotalLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    subtotalValue->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    serviceLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    serviceValue->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    totalLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    totalValue->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    detailsGrid->addWidget(subtotalLabel, 0, 0);
    detailsGrid->addWidget(subtotalValue, 0, 1);
    detailsGrid->addWidget(serviceLabel, 1, 0);
    detailsGrid->addWidget(serviceValue, 1, 1);
    detailsGrid->addWidget(totalLabel, 2, 0);
    detailsGrid->addWidget(totalValue, 2, 1);

    mainLayout->addWidget(detailsSection);

    // --- Order Completed Button ---
    QWidget *buttonSection = new QWidget(card);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonSection);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->addStretch();

    QPushButton *completeBtn = new QPushButton("Order Completed", buttonSection);
    completeBtn->setStyleSheet("background-color: #28a745; color: white; border-radius: 8px; padding: 14px 48px; font-size: 20px; font-weight: bold;");
    completeBtn->setFixedHeight(48);

    buttonLayout->addWidget(completeBtn);
    buttonLayout->addStretch();

    mainLayout->addSpacing(24);
    mainLayout->addWidget(buttonSection);

    // Connect button to close dialog
    connect(completeBtn, &QPushButton::clicked, this, [=]() {
        QSqlDatabase &db = DatabaseManager::getDatabase();


        if (!db.transaction()) {
            qDebug() << "Failed to start transaction:" << db.lastError();
            return;
        }

        QSqlQuery updateStatus(db);
        updateStatus.prepare("UPDATE orders SET status = ? WHERE order_id = ?");
        updateStatus.addBindValue("Billed");
        updateStatus.addBindValue(orderId);

        if (!updateStatus.exec()) {
            qDebug() << "Failed to update order status:" << updateStatus.lastError();
            db.rollback();
            return;
        }

        QSqlQuery updateTable(db);
        updateTable.prepare("UPDATE tables SET status = 'available', order_id = NULL WHERE order_id = ?");
        updateTable.addBindValue(orderId);

        if (!updateTable.exec()) {
            qDebug() << "Failed to update table status:" << updateTable.lastError();
            db.rollback();
            return;
        }

        if (!db.commit()) {
            qDebug() << "Failed to commit transaction:" << db.lastError();
            db.rollback();
            return;
        }

        qDebug() << "Order completed and table status updated successfully.";
        this->accept();  // closes the dialog
    });



    // Apply layout to frame
    QVBoxLayout *frameLayout = new QVBoxLayout(ui->frame);
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addWidget(card);
    ui->frame->setLayout(frameLayout);
}

checkout::~checkout()
{
    delete ui;
}
