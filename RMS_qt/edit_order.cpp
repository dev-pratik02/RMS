#include "edit_order.h"
#include "ui_edit_order.h"


edit_order::edit_order(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_order)
{
    ui->setupUi(this);
}

edit_order::edit_order(const QString &orderId, const QString &table, const QString &time, const QString &status,
                       const QList<QList<QString>> &items, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_order)
{
    ui->setupUi(this);


    orderIdGlobal = orderId;

    // Remove any layout from the frame
    QLayout *oldLayout = ui->frame->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // Only add the database if it doesn't already exist
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("/Users/pratik/Programming/RMS/RMS_qt/RmsApp.db");
    } else {
        mydb = QSqlDatabase::database("qt_sql_default_connection");
    }

    if(mydb.open()){
        qDebug() <<"Database is connected by edit orders page";
    }
    else{
        qDebug() << "Database connection failed" ;
        qDebug() << "Error:"<< mydb.lastError();
    }


    // --- Card Layout ---
    QWidget *card = new QWidget(ui->frame);
    card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    card->setStyleSheet(
        "background-color: #333;"
        "border-radius: 8px;"
        "padding: 12px;"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout(card);
    mainLayout->setContentsMargins(18, 18, 18, 18);
    mainLayout->setSpacing(10);

    // --- Top Section ---
    QWidget *topSection = new QWidget(card);
    QGridLayout *topGrid = new QGridLayout(topSection);
    topGrid->setContentsMargins(0, 0, 0, 0);
    topGrid->setHorizontalSpacing(12);
    topGrid->setVerticalSpacing(4);

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
    headerLayout->setSpacing(0); // No spacing between header widgets

    // Set more width for Name column and increase gap between Name and Quantity
    int nameColWidth = 150;
    int qtyColWidth = 100;
    int priceColWidth = 80;
    int nameQtyGap = 200;
    int qtyPriceGap=100;

    QLabel *nameLabel = new QLabel("Name", headerWidget);
    QLabel *qtyLabel = new QLabel("Quantity", headerWidget);
    QLabel *priceLabel = new QLabel("Price", headerWidget);

    nameLabel->setStyleSheet("color: white; background: transparent; font-size: 16px; font-weight: bold; padding: 6px 8px;");
    qtyLabel->setStyleSheet("color: white; background: transparent; font-size: 16px; font-weight: bold; padding: 6px 8px;");
    priceLabel->setStyleSheet("color: white; background: transparent; font-size: 16px; font-weight: bold; padding: 6px 8px;");

    nameLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    qtyLabel->setAlignment(Qt::AlignCenter);
    priceLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    nameLabel->setFixedWidth(nameColWidth);
    qtyLabel->setFixedWidth(qtyColWidth);
    priceLabel->setFixedWidth(priceColWidth);

    headerLayout->addWidget(nameLabel);
    headerLayout->addSpacing(nameQtyGap);
    headerLayout->addWidget(qtyLabel);
    headerLayout->addSpacing(qtyPriceGap);
    headerLayout->addWidget(priceLabel);

    mainLayout->addWidget(headerWidget);

    // --- Order Table (no headers) ---
    QTableWidget *orderTable = new QTableWidget(items.size(), 3, card);
    orderTable->horizontalHeader()->setVisible(false);
    orderTable->verticalHeader()->setVisible(false);
    orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    orderTable->setFocusPolicy(Qt::NoFocus);
    orderTable->setSelectionMode(QAbstractItemView::NoSelection);
    orderTable->setShowGrid(false);
    orderTable->setMinimumHeight(300);
    orderTable->setStyleSheet(
        "QTableWidget {"
        " background-color: #333;"
        " color: white;"
        " border: none;"
        " font-size: 15px;"
        " gridline-color: transparent;"
        "}"
        "QTableWidget::item {"
        " padding: 6px;"
        " background: transparent;"
        "}"
    );
    // Increase spacing between order items column and quantity column by making name column wider
    orderTable->setColumnWidth(0, nameColWidth + nameQtyGap);
    orderTable->setColumnWidth(1, qtyColWidth + qtyPriceGap);
    orderTable->setColumnWidth(2, priceColWidth);


    //Creating a menu list by fetching menu from database

    QSqlQuery queryMenuList(mydb);
    if(queryMenuList.exec("SELECT * FROM menu")){
        qDebug()<<"Successfully fetched menu details";
    }
    else{
        qDebug()<< "Can't fetch menu details";
        qDebug() << "Error:" << queryMenuList.lastError();
    }

    QStringList menuList;
    // For SQLite, count rows manually:
    int records = 0;
    while (queryMenuList.next()) {
        ++records;
        QString menu_item_name=queryMenuList.value(1).toString();
        menuList.append(menu_item_name);
    }
    qDebug() << "Number of records:" << records;
    queryMenuList.first();

    for (int i = 0; i < items.size(); ++i) {
        // --- ComboBox for menu item (editable, default to card value) ---
        QComboBox *combo = new QComboBox(orderTable);
        combo->setEditable(true);
        combo->addItems(menuList);
        QString itemName = items[i].value(0);
        int idx = menuList.indexOf(itemName);
        if (idx < 0) {
            combo->addItem(itemName);
            combo->setCurrentIndex(combo->count() - 1);
        } else {
            combo->setCurrentIndex(idx);
        }
        combo->setEditText(itemName);
        // Add slight outline to dropdown
        combo->setStyleSheet(
            "QComboBox, QComboBox QAbstractItemView, QLineEdit {"
            " background: #333;"
            " color: white;"
            " border: 1px solid #555;"
            " border-radius: 4px;"
            " padding: 2px 6px;"
            " font-size: 14px;"
            " selection-background-color: #0078d7;"
            " selection-color: #fff;"
            "}"
        );
        orderTable->setCellWidget(i, 0, combo);

        // --- SpinBox for quantity (editable, default to card value) ---
        QSpinBox *spin = new QSpinBox(orderTable);
        spin->setMinimum(1);
        spin->setMaximum(1000);
        bool ok = false;
        int qty = items[i].value(1).toInt(&ok);
        spin->setValue(ok && qty > 0 ? qty : 1);
        spin->setAlignment(Qt::AlignCenter);
        // Add slight outline to spinbox
        spin->setStyleSheet(
            "QSpinBox {"
            " background: #333;"
            " color: white;"
            " border: 1px solid #555;"
            " border-radius: 4px;"
            " padding: 2px 6px;"
            " font-size: 14px;"
            "}"
        );
        orderTable->setCellWidget(i, 1, spin);

        // --- Price (not editable) ---
        QTableWidgetItem *priceItem = new QTableWidgetItem(items[i].value(2));
        priceItem->setTextAlignment(Qt::AlignCenter);
        orderTable->setItem(i, 2, priceItem);

        comboBoxes.append(combo);
        spinBoxes.append(spin);

    }

    mainLayout->addWidget(orderTable);

    // --- Action Buttons ---
    QWidget *actionSection = new QWidget(card);
    QHBoxLayout *actionLayout = new QHBoxLayout(actionSection);
    actionLayout->setContentsMargins(0, 0, 0, 0);
    actionLayout->setSpacing(16);

    QPushButton *readyBtn = new QPushButton("Mark as Ready", actionSection);
    QPushButton *servedBtn = new QPushButton("Mark as Served", actionSection);
    QPushButton *delBtn = new QPushButton("Delete Order", actionSection);

    readyBtn->setStyleSheet("background-color: #28a745; color: white; border-radius: 6px; padding: 8px 18px; font-size: 14px; font-weight: bold;");
    servedBtn->setStyleSheet("background-color: #0078d7; color: white; border-radius: 6px; padding: 8px 18px; font-size: 14px; font-weight: bold;");
    delBtn->setStyleSheet("background-color: #6c757d; color: white; border-radius: 6px; padding: 8px 18px; font-size: 14px; font-weight: bold;");

    readyBtn->setFixedHeight(36);
    servedBtn->setFixedHeight(36);
    delBtn->setFixedHeight(36);

    actionLayout->addWidget(readyBtn);
    actionLayout->addWidget(servedBtn);
    actionLayout->addWidget(delBtn);
    mainLayout->addWidget(actionSection);

    // --- Reset & Save Buttons ---
    QWidget *saveResetSection = new QWidget(card);
    QHBoxLayout *saveResetLayout = new QHBoxLayout(saveResetSection);
    saveResetLayout->setContentsMargins(0, 0, 0, 0);
    saveResetLayout->setSpacing(18);

    QPushButton *resetBtn = new QPushButton("Reset", saveResetSection);
    QPushButton *saveBtn = new QPushButton("Save", saveResetSection);

    saveBtn->setStyleSheet("background-color: #0078d7; color: white; border-radius: 6px; padding: 8px 32px; font-size: 15px; font-weight: bold;");
    resetBtn->setStyleSheet("background-color: #fff; color: #222; border-radius: 6px; padding: 8px 32px; font-size: 15px; font-weight: bold; border: 1px solid #ccc;");

    saveBtn->setFixedHeight(38);
    resetBtn->setFixedHeight(38);

    saveResetLayout->addStretch();
    saveResetLayout->addWidget(resetBtn);
    saveResetLayout->addWidget(saveBtn);

    mainLayout->addSpacing(8);
    mainLayout->addWidget(saveResetSection);

    connect(resetBtn, &QPushButton::clicked, this, [=]() {
        this->done(1234);
    });
    connect(saveBtn, &QPushButton::clicked, this, &edit_order::onSaveClicked);
    connect(readyBtn, &QPushButton::clicked, this, [=]() { updateStatus("Ready"); });
    connect(servedBtn, &QPushButton::clicked, this, [=]() { updateStatus("Served"); });
    connect(delBtn, &QPushButton::clicked, this, [=]() {
        QSqlQuery querydelitems(mydb);
        querydelitems.prepare("delete from order_items where order_id= ?");
        querydelitems.addBindValue(orderId);
        if(querydelitems.exec()){
            qDebug()<<"Order: "<<orderId<<"deleted successfully";
        }
        else{
            qDebug()<<"Order: "<<orderId<<"could not be deleted";
        }

        QSqlQuery querydelorder(mydb);
        querydelorder.prepare("delete from orders where order_id= ?");
        querydelorder.addBindValue(orderId);
        if(querydelorder.exec()){
            qDebug()<<"Order: "<<orderId<<"deleted successfully";
        }
        else{
            qDebug()<<"Order: "<<orderId<<"could not be deleted";
        }
        this->accept();
    });

    // Apply layout to frame
    QVBoxLayout *frameLayout = new QVBoxLayout(ui->frame);
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addWidget(card);
    ui->frame->setLayout(frameLayout);
}

edit_order::~edit_order()
{
    delete ui;
}

void edit_order::onSaveClicked() {
    for (int i = 0; i < comboBoxes.size(); ++i) {
        QString itemName = comboBoxes[i]->currentText();
        int quantity = spinBoxes[i]->value();

        // Look up menu_item_id from item name
        QSqlQuery query(mydb);
        query.prepare("SELECT menu_item_id FROM menu WHERE item_name = ?");
        query.addBindValue(itemName);
        QString menuId = "unknown";
        if (query.exec() && query.next()) {
            menuId = query.value(0).toString();
        }

        // You can now update or insert into order_items
        QSqlQuery upsert(mydb);
        upsert.prepare("UPDATE order_items SET menu_item_id = ?, quantity = ? "
                       "WHERE order_id = ? AND item_id = ("
                       "  SELECT item_id FROM order_items WHERE order_id = ? LIMIT 1 OFFSET ?)");
        upsert.addBindValue(menuId);
        upsert.addBindValue(quantity);
        upsert.addBindValue(orderIdGlobal);
        upsert.addBindValue(orderIdGlobal);
        upsert.addBindValue(i);

        if (!upsert.exec()) {
            qDebug() << "Failed to update row" << i << ":" << upsert.lastError();
        }
    }

    qDebug() << "Order updated successfully.";
    this->accept();

}

void edit_order::updateStatus(const QString &newStatus) {
    QSqlQuery updateStatus(mydb);
    updateStatus.prepare("UPDATE orders SET status = ? WHERE order_id = ?");
    updateStatus.addBindValue(newStatus);
    updateStatus.addBindValue(orderIdGlobal);
    if (updateStatus.exec()) {
        qDebug() << "Order status updated to" << newStatus;
    } else {
        qDebug() << "Failed to update status:" << updateStatus.lastError();
    }
    this->accept();
}




