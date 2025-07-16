#include "edit_order.h"
#include "ui_edit_order.h"
#include "databasemanager.h"

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

    QSqlDatabase &db = DatabaseManager::getDatabase();





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

    // Order Table
    QTableWidget *orderTable = new QTableWidget(items.size(), 4, card);

    // Show horizontal headers (default is visible, but be explicit)
    orderTable->horizontalHeader()->setVisible(true);

    // Optionally, hide vertical headers (row numbers)
    orderTable->verticalHeader()->setVisible(false);

    // Set header labels
    QStringList headerLabels = {"Name", "Quantity", "Price", "Action"};
    orderTable->setHorizontalHeaderLabels(headerLabels);

    // Disable editing for the cells (you can allow editing on widgets inside cells)
    orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // Ensure horizontal header is visible
    orderTable->horizontalHeader()->setVisible(true);

    // Set the horizontal header text alignment and style if needed
    orderTable->horizontalHeader()->setHighlightSections(false);

    // Optionally force a style to make the header text visible and background contrasting
    orderTable->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        "font-weight: bold;"
        "font-size: 15px;"
        "padding: 2px;"
        "border: none;"
        "}"
        );
    // Selection modes, grid, et
    orderTable->horizontalHeader()->setFixedHeight(50);
    orderTable->setFocusPolicy(Qt::NoFocus);
    orderTable->setSelectionMode(QAbstractItemView::NoSelection);
    orderTable->setShowGrid(false);
    orderTable->setMinimumHeight(300);
    orderTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

    // Set column widths
    orderTable->setColumnWidth(0, 250);
    orderTable->setColumnWidth(1, 180);
    orderTable->setColumnWidth(2, 80);
    orderTable->setColumnWidth(3, 100);



    //Creating a menu list by fetching menu from database

    QSqlQuery queryMenuList(db);
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
    qDebug() << "Number of menu items:" << records;
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

        // --- Delete Button ---
        QPushButton *deleteRowBtn = new QPushButton("Delete");
        deleteRowBtn->setStyleSheet("background-color: #dc3545; color: white; border-radius: 4px; padding: 4px 8px;");
        orderTable->setCellWidget(i, 3, deleteRowBtn);

        // Needed to find out which row to delete
        connect(deleteRowBtn, &QPushButton::clicked, this, [=]() {
            QPushButton* btn = qobject_cast<QPushButton*>(sender());
            if (!btn) return;
            // Find row by searching for widget
            int row = -1;
            for (int r = 0; r < orderTable->rowCount(); ++r) {
                if (orderTable->cellWidget(r, 3) == btn) {
                    row = r;
                    break;
                }
            }
            if (row >= 0) {
                deleteItemRow(orderTable, row);
            }
        });


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




        if (!db.transaction()) {
            qDebug() << "Failed to start transaction:" << db.lastError();
            return;
        }

        QSqlQuery querydelitems(db);
        querydelitems.prepare("DELETE FROM order_items WHERE order_id = ?");
        querydelitems.addBindValue(orderId);
        bool ok1 = querydelitems.exec();
        if (!ok1)
            qDebug() << "Delete order_items failed:" << querydelitems.lastError();

        QSqlQuery querydelorder(db);
        querydelorder.prepare("DELETE FROM orders WHERE order_id = ?");
        querydelorder.addBindValue(orderId);
        bool ok2 = querydelorder.exec();
        if (!ok2)
            qDebug() << "Delete orders failed:" << querydelorder.lastError();

        QSqlQuery querytableStatus(db);
        querytableStatus.prepare("UPDATE tables SET status = 'available' WHERE order_id = ?");
        querytableStatus.addBindValue(orderId);
        bool ok4 = querytableStatus.exec();

        QSqlQuery querydeltable(db);
        querydeltable.prepare("UPDATE tables SET order_id = NULL WHERE order_id = ?");
        querydeltable.addBindValue(orderId);
        bool ok3 = querydeltable.exec();
        if (!ok3)
            qDebug() << "Update tables (order_id=NULL) failed:" << querydeltable.lastError();

        if (!ok4)
            qDebug() << "Update tables (status=available) failed:" << querytableStatus.lastError();

        if (ok1 && ok2 && ok3 && ok4) {
            if (!db.commit()) {
                qDebug() << "Failed to commit transaction:" << db.lastError();
                db.rollback();
            } else {
                qDebug() << "All queries committed successfully";
            }
        } else {
            db.rollback();
            qDebug() << "Transaction failed, rolled back";
        }



        this->accept();
    });

    // Apply layout to frame
    QVBoxLayout *frameLayout = new QVBoxLayout(ui->frame);
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addWidget(card);
    ui->frame->setLayout(frameLayout);
}


void edit_order::deleteItemRow(QTableWidget *table, int row)
{
    if (row < 0 || row >= table->rowCount())
        return;

    // Remove widgets from comboBoxes and spinBoxes
    if (row < comboBoxes.size())
        comboBoxes.removeAt(row);
    if (row < spinBoxes.size())
        spinBoxes.removeAt(row);

    // Remove row from the table
    table->removeRow(row);
}

edit_order::~edit_order()
{
    delete ui;
}

void edit_order::onSaveClicked() {
    // Start transaction for safety
    if (!db.transaction()) {
        qDebug() << "Failed to start transaction:" << db.lastError();
        return;
    }

    // Step 1: Delete all existing order_items for this order
    QSqlQuery deleteQuery(db);
    deleteQuery.prepare("DELETE FROM order_items WHERE order_id = ?");
    deleteQuery.addBindValue(orderIdGlobal);
    if (!deleteQuery.exec()) {
        qDebug() << "Failed to delete existing order items:" << deleteQuery.lastError();
        db.rollback();
        return;
    }

    // Step 2: Insert all current rows from UI
    for (int i = 0; i < comboBoxes.size(); ++i) {
        QString itemName = comboBoxes[i]->currentText();
        int quantity = spinBoxes[i]->value();

        // Look up menu_item_id from item name
        QSqlQuery query(db);
        query.prepare("SELECT menu_item_id FROM menu WHERE item_name = ?");
        query.addBindValue(itemName);
        QString menuId = "unknown";
        if (query.exec() && query.next()) {
            menuId = query.value(0).toString();
        }

        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO order_items (order_id, menu_item_id, quantity) VALUES (?, ?, ?)");
        insertQuery.addBindValue(orderIdGlobal);
        insertQuery.addBindValue(menuId);
        insertQuery.addBindValue(quantity);

        if (!insertQuery.exec()) {
            qDebug() << "Failed to insert order item:" << insertQuery.lastError();
            db.rollback();
            return;
        }
    }

    // Commit transaction
    if (!db.commit()) {
        qDebug() << "Failed to commit transaction:" << db.lastError();
        db.rollback();
        return;
    }

    qDebug() << "Order updated successfully.";
    this->accept();
}


void edit_order::updateStatus(const QString &newStatus) {
    QSqlQuery updateStatus(db);
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




