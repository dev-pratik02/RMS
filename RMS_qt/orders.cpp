// orders.cpp
#include "orders.h"
#include "ui_orders.h"
#include "databasemanager.h"
#include "globals.h"

QString currentStatus = "";
const QString activeButtonStyle = R"(
    background-color: #0078d7;
    color: white;
    font-weight: bold;
    border-radius: 8px;
    padding: 5px;
)";

const QString inactiveButtonStyle = R"(
    background-color: #000000;
    color: white;
    border-radius: 8px;
    padding:5px;
)";

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

    if(g_userRole == "Waiter"){
        currentStatus = "Ready";
        ui->btn_widget->setVisible(false);
    }else if(g_userRole == "Kitchen"){
        currentStatus = "Preparing";
        ui->btn_widget->setVisible(false);
    }
    ordersPageSetup();

}


void orders::ordersPageSetup(){

    //Fetching data from database

    QSqlDatabase &db = DatabaseManager::getDatabase();
    QSqlQuery queryInsert(db);
    if(currentStatus.isEmpty()){
        setActiveButton(ui->btn_all);
        queryInsert.prepare("SELECT * FROM orders where status!= 'Billed'");
    }
    else{
        queryInsert.prepare("SELECT * FROM orders where status = ?");
        queryInsert.addBindValue(currentStatus);

        //styling current status button
        if(currentStatus == "Preparing"){
            setActiveButton(ui->btn_preparing);
        }
        else if(currentStatus == "Ready"){
            setActiveButton(ui->btn_ready);
        }
        else if(currentStatus == "Served"){
            setActiveButton(ui->btn_served);
        }
    }
    if(queryInsert.exec()){
        qDebug()<<"Successfully fetched order details";
    }
    else{
        qDebug()<< "Can't fetch order details";
        qDebug() << "Error:" << queryInsert.lastError();
    }



    // For SQLite, count rows manually:
    int records = 0;
    while (queryInsert.next()) {
        ++records;
    }
    qDebug() << "Number of records:" << records;
    queryInsert.first();

    if(records == 0){
        qDebug() << "no orders";
        ui->recordLabel->setText("There are no orders of the status: " + currentStatus);
        ui->recordLabel->setAlignment(Qt::AlignCenter);
        ui->recordLabel->setStyleSheet("font-size: 16px; color: white; padding: 10px;");
        ui->recordLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->recordLabel->show();
        return;
    }

    else{
        ui->recordLabel->hide();
        const int columns = 3;
        const int cardWidth = 200;
        const int cardHeight = 200;
        const int hSpacing = 12;
        const int vSpacing = 12;
        const int count = records;
        int rows = (count + columns - 1) / columns;

        QWidget *dynamicCardContainer = new QWidget;
        QGridLayout *gridLayout = new QGridLayout(dynamicCardContainer);
        gridLayout->setSpacing(vSpacing);
        gridLayout->setHorizontalSpacing(hSpacing);
        gridLayout->setVerticalSpacing(vSpacing);
        gridLayout->setContentsMargins(0, 0, 0, 0);


        int i=0;
        do{
            int row = i / columns;
            int col = i % columns;
            QWidget *card = createOrderCard(
                queryInsert.value(0).toString(),
                queryInsert.value(1).toString(),
                queryInsert.value(2).toString(),
                queryInsert.value(3).toString()
                );
            gridLayout->addWidget(card, row, col);
            ++i;
        }while(queryInsert.next());

        queryInsert.finish();

        // Set a minimum size for the container so the scroll area works
        dynamicCardContainer->setMinimumSize(
            columns * cardWidth + (columns - 1) * hSpacing,
            rows * cardHeight + (rows - 1) * vSpacing
            );

        ui->scrollArea->setWidget(dynamicCardContainer);
    }
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

    // --- Top Section: 2x2 grid for info labels ---
    QWidget *topSection = new QWidget(card);
    QGridLayout *topGrid = new QGridLayout(topSection);
    topGrid->setContentsMargins(0, 0, 0, 0);
    topGrid->setHorizontalSpacing(2);
    topGrid->setVerticalSpacing(0);

    QString labelStyle = "color: white; background: transparent; border: none; font-size: 10px;";
    QString labelStyleImp = "color: white; background: transparent; border: none; font-size: 14px;";

    QLabel *idLabel = new QLabel("Order #" + orderId, topSection);
    QLabel *timeLabel = new QLabel("Time: " + time, topSection);
    QLabel *tableLabel = new QLabel("Table: " + table, topSection);
    QLabel *statusLabel = new QLabel("Status: " + status, topSection);

    idLabel->setStyleSheet(labelStyle);
    timeLabel->setStyleSheet(labelStyle);
    tableLabel->setStyleSheet(labelStyleImp);
    statusLabel->setStyleSheet(labelStyle);

    idLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    timeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    tableLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    statusLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    idLabel->setWordWrap(true);
    timeLabel->setWordWrap(true);
    tableLabel->setWordWrap(true);
    statusLabel->setWordWrap(true);

    topGrid->addWidget(tableLabel, 0, 0);
    topGrid->addWidget(idLabel, 1, 0);
    topGrid->addWidget(timeLabel, 0, 1);
    topGrid->addWidget(statusLabel, 1, 1);

    mainLayout->addWidget(topSection);

    // --- Table Header as Labels (aligned with table columns) ---
    QWidget *headerWidget = new QWidget(card);
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(0);

    // Set column widths for both header and table
    int nameColWidth = 90;
    int qtyColWidth = 30;
    int priceColWidth = 60;

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


    //Fetching orders from Database
    QSqlQuery queryOrders(db);
    QSqlQuery queryMenu(db);
    // Use parameterized query to avoid SQL injection and ensure correct value substitution
    queryOrders.prepare("SELECT * FROM order_items WHERE order_id = ?");
    queryOrders.addBindValue(orderId);

    if(queryOrders.exec()){
        // qDebug() << "Successfully fetched order items for order_id:" << orderId;
    }
    else {
        qDebug() << "Failed to obtain the order items for order_id:" << orderId;
        qDebug() << queryOrders.lastError();
    }

    int orders_row = 0;
    while (queryOrders.next()) {
        ++orders_row;
    }
    // qDebug() << "Number of order items:" << orders_row;

    // Reset query to first record for reading data
    if (orders_row > 0)
        queryOrders.first();


    // --- Middle Section: Table of order items (6 rows, no headers) ---
    QTableWidget *orderTable = new QTableWidget(orders_row, 3, card);
    orderTable->horizontalHeader()->setVisible(false);
    orderTable->verticalHeader()->setVisible(false);
    orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    orderTable->setFocusPolicy(Qt::NoFocus);
    orderTable->setSelectionMode(QAbstractItemView::NoSelection);
    orderTable->setShowGrid(false);
    orderTable->setFixedHeight(180);
    orderTable->setStyleSheet(
        "QTableWidget {"
        " background: #222;"
        " color: white;"
        " border: none;"
        " font-size: 10px;"
        "}"
        "QTableWidget::item {"
        " padding: 2px 4px;"
        " background: transparent;"
        "}"
        );
    orderTable->setColumnWidth(0, nameColWidth);
    orderTable->setColumnWidth(1, qtyColWidth);
    orderTable->setColumnWidth(2, priceColWidth);


    // Prepare order items for passing
    QList<QList<QString>> items;

    // Fill orders in the card
    int i=0;
    if (orders_row > 0 && queryOrders.first()) {
        do {
            // Fetch menu item details for each order item
            queryMenu.prepare("SELECT item_name, price FROM menu WHERE menu_item_id = ?");
            QString menuItemId = queryOrders.value(2).toString().trimmed();
            queryMenu.addBindValue(menuItemId);
            // qDebug() << "Looking up menu_item_id:" << menuItemId;

            QString itemname;
            double price = 0.0;

            if (queryMenu.exec()) {
                if (queryMenu.next()) {
                    itemname = queryMenu.value(0).toString();
                    price = queryMenu.value(1).toDouble();
                } else {
                    qDebug() << "No match in menu table for menu_item_id:" << menuItemId;
                    itemname = "Unknown";
                }
            } else {
                qDebug() << "Menu query failed:" << queryMenu.lastError();
                itemname = "Unknown";
            }

            QString qtyStr = queryOrders.value(3).toString();
            int quantity = qtyStr.toInt();
            double totalprice = price * quantity;

            QTableWidgetItem *item0 = new QTableWidgetItem(itemname);
            QTableWidgetItem *item1 = new QTableWidgetItem(qtyStr);
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(totalprice, 'f', 2));
            item0->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            item1->setTextAlignment(Qt::AlignCenter);
            item2->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            orderTable->setItem(i, 0, item0);
            orderTable->setItem(i, 1, item1);
            orderTable->setItem(i, 2, item2);

            //append value to the list for passing later
            items.append({itemname, qtyStr, QString::number(totalprice, 'f', 2)});
            ++i;

        } while (queryOrders.next());
    }
    queryOrders.finish();
    queryMenu.finish();

    mainLayout->addWidget(orderTable);


    // --- Bottom Section: Buttons ---

    QWidget *bottomSection = new QWidget(card);
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomSection);
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    bottomLayout->setSpacing(6);

    if(g_userRole == "Manager" || g_userRole == "Admin"){
        QPushButton *editBtn = new QPushButton("Edit", bottomSection);
        QPushButton *checkoutBtn = new QPushButton("Checkout", bottomSection);

        editBtn->setStyleSheet("background-color: #555; color: white; border-radius: 4px; padding: 2px 8px; font-size: 10px;");
        checkoutBtn->setStyleSheet("background-color: #0078d7; color: white; border-radius: 4px; padding: 2px 8px; font-size: 10px;");

        editBtn->setFixedHeight(18);
        checkoutBtn->setFixedHeight(18);

        bottomLayout->addWidget(editBtn);
        bottomLayout->addWidget(checkoutBtn);

        mainLayout->addWidget(bottomSection);

        connect(editBtn, &QPushButton::clicked, this, [=]() {
            edit_order *dlg = new edit_order(orderId, table, time, status, items, card);
            dlg->setAttribute(Qt::WA_DeleteOnClose);

            // Connect to finished signal to refresh when dialog closes
            connect(dlg, &QDialog::finished, this, [=](int result) {
                if (result == QDialog::Accepted) {
                    this->close();
                    ptrorders = new orders();
                    ptrorders->show();
                }
                else if ( result == 1234){
                    edit_order *newdlg = new edit_order(orderId, table, time, status, items, card);
                    newdlg->setAttribute(Qt::WA_DeleteOnClose);
                    newdlg->show();
                }
            });

            dlg->show();
        });

        connect(checkoutBtn, &QPushButton::clicked, this, [=]() {
            checkout *dlg = new checkout(orderId, table, time, status, items, card);
            dlg->setAttribute(Qt::WA_DeleteOnClose);

            connect(dlg, &QDialog::finished, this, [=](int result) {
                if (result == QDialog::Accepted) {
                    this->close();
                    ptrorders = new orders();
                    ptrorders->show();
                }
            });

            dlg->show();
        });
    }
    else if(g_userRole == "Waiter"){
        QPushButton *served_btn = new QPushButton("Mark as Served",bottomSection);
        served_btn->setStyleSheet("background-color: #0078d7; color: white; border-radius: 4px; padding: 2px 8px; font-size: 10px;");
        served_btn->setFixedHeight(18);
        bottomLayout->addWidget(served_btn);
        mainLayout->addWidget(bottomSection);
        connect(served_btn, &QPushButton::clicked, this, [=]() {
            QSqlDatabase &db = DatabaseManager::getDatabase();
            QSqlQuery updateStatus(db);
            updateStatus.prepare("UPDATE orders SET status = 'Served' WHERE order_id = ?");
            updateStatus.addBindValue(orderId);
            if (updateStatus.exec()) {
                qDebug() << "Order status updated to Served";
            } else {
                qDebug() << "Failed to update status:" << updateStatus.lastError();
            }
            updateStatus.finish();
            this->close();
            ptrorders = new orders();
            ptrorders->show();
        });
    }
    else if(g_userRole == "Kitchen"){
        QPushButton *ready_btn = new QPushButton("Mark as Ready",bottomSection);
        ready_btn->setStyleSheet("background-color: #0078d7; color: white; border-radius: 4px; padding: 2px 8px; font-size: 10px;");
        ready_btn->setFixedHeight(18);
        bottomLayout->addWidget(ready_btn);
        mainLayout->addWidget(bottomSection);
        connect(ready_btn, &QPushButton::clicked, this, [=]() {
            QSqlDatabase &db = DatabaseManager::getDatabase();
            QSqlQuery updateStatus(db);
            updateStatus.prepare("UPDATE orders SET status = 'Ready' WHERE order_id = ?");
            updateStatus.addBindValue(orderId);
            if (updateStatus.exec()) {
                qDebug() << "Order status updated to Ready";
            } else {
                qDebug() << "Failed to update status:" << updateStatus.lastError();
            }
            updateStatus.finish();
            this->close();
            ptrorders = new orders();
            ptrorders->show();
        });
    }

    return card;
}


void orders::setActiveButton(QPushButton* activeBtn) {
    QList<QPushButton*> buttons = {
        ui->btn_all,
        ui->btn_preparing,
        ui->btn_ready,
        ui->btn_served,
    };

    for (QPushButton* btn : buttons) {
        if (btn == activeBtn) {
            btn->setStyleSheet(activeButtonStyle);
        } else {
            btn->setStyleSheet(inactiveButtonStyle);
        }
    }
}

void orders::on_btn_preparing_clicked()
{
    currentStatus = "Preparing";
    this->close();
    ptrorders = new orders();
    ptrorders->show();
}


void orders::on_btn_ready_clicked()
{
    currentStatus = "Ready";
    this->close();
    ptrorders = new orders();
    ptrorders->show();
}


void orders::on_btn_served_clicked()
{
    currentStatus = "Served";
    this->close();
    ptrorders = new orders();
    ptrorders->show();
}


void orders::on_btn_all_clicked()
{
    currentStatus = "";
    this->close();
    ptrorders = new orders();
    ptrorders->show();
}

orders::~orders()
{
    delete ui;
}
