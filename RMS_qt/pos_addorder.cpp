#include "pos_addorder.h"
#include "ui_pos_addorder.h"
#include "mainwindow.h"
#include "databasemanager.h"
// Constructor for POS_AddOrder
POS_AddOrder::POS_AddOrder(QString table_no,class pos *posWindow, MainWindow *mainWindow, QWidget *parent)
    : QWidget(parent), ui(nullptr), m_posWindow(posWindow), m_mainWindow(mainWindow)
{
    // Set window title and size
    setWindowTitle("POS - Add Order");
    setMinimumSize(1280, 800);
    resize(1280, 800);
    qDebug() << "The received table no. is " << table_no;

    QSqlDatabase mydb = DatabaseManager::getDatabase();

    db = mydb;



    // Main layout of the screen (horizontal split)
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // Left side container for categories and item grid
    QVBoxLayout *leftContainer = new QVBoxLayout();

    // Create the item grid layout inside a widget
    QWidget *itemsWidget = new QWidget();
    itemsLayout = new QGridLayout(itemsWidget);

    // Setup horizontal category bar
    QWidget *categoryWidget = new QWidget();
    QHBoxLayout *categoryLayout = new QHBoxLayout(categoryWidget);
    QButtonGroup *categoryGroup = new QButtonGroup(this);
    categoryGroup->setExclusive(true);


    // Scroll area for categories
    QScrollArea *categoryScroll = new QScrollArea();
    categoryScroll->setWidgetResizable(true);
    categoryScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    categoryScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    categoryScroll->setFixedHeight(60);
    categoryScroll->setWidget(categoryWidget);

    // Scroll area for item grid
    QScrollArea *itemsScroll = new QScrollArea();
    itemsScroll->setWidgetResizable(true);
    itemsScroll->setWidget(itemsWidget);

    // Add scroll areas to the left container
    leftContainer->addWidget(categoryScroll);
    leftContainer->addWidget(itemsScroll);

    // Right side container for order details and actions
    QVBoxLayout *rightContainer = new QVBoxLayout();

    // Display table and order ID information
    QString table_status, order_id;
    orderInfoLabel = new QLabel("Table No: " + table_no + "\n\nOrder ID: " + order_id);
    orderInfoLabel->setStyleSheet(R"(
        font-size: 14px;
        font-weight: bold;
        padding: 6px;
        margin-bottom: 15px;
    )");
    rightContainer->addWidget(orderInfoLabel,0);

    QPushButton *btnAddNotes = new QPushButton("Add Notes");
    rightContainer->addWidget(btnAddNotes);
    connect(btnAddNotes, &QPushButton::clicked, this, &POS_AddOrder::onAddNotesClicked);

    // Create table to show ordered items
    orderTable = new QTableWidget(0, 4, this);
    orderTable->setHorizontalHeaderLabels({"Item", "No.", "Price", "Action"});
    orderTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    orderTable->verticalHeader()->setVisible(false);
    orderTable->setShowGrid(false);
    orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    orderTable->setSelectionMode(QAbstractItemView::NoSelection);
    orderTable->setFocusPolicy(Qt::NoFocus);
    // orderTable->setFixedHeight(300);
    orderTable->verticalHeader()->setDefaultSectionSize(40);

    // Set styles for the order table
    orderTable->setStyleSheet(R"(
        QTableWidget {
            background-color: #1e1e1e;
            border: none;
            font-size: 14px;
        }
        QHeaderView::section {
            background-color: #2a2a2a;
            font-weight: bold;
            padding: 8px;
            font-size: 14px;
            border-bottom: 1px solid #ccc;
        }
        QTableWidget::item {
            padding: 8px;
            background-color: transparent;
        }
        QTableWidget::item:selected {
            background-color: #444444;
        }
    )");

    rightContainer->addWidget(orderTable,8);


    // Create a container widget for subtotal, service charge, and total
    QWidget *totalsContainer = new QWidget();
    QVBoxLayout *totalsLayout = new QVBoxLayout(totalsContainer);

    // Labels to show subtotal, service charge, and total
    subtotalLabel = new QLabel("Subtotal:\tRs. 0");
    serviceChargeLabel = new QLabel("Service Charge:\tRs. 0");
    totalLabel = new QLabel("<b>Total:\tRs. 0</b>");
    subtotalLabel->setStyleSheet("font-size: 16px; margin-bottom: 2px;");
    serviceChargeLabel->setStyleSheet("font-size: 12px; margin-bottom: 2px;");
    totalLabel->setStyleSheet("font-size: 20px; font-weight:bold; margin-bottom: 6px;");


    // Add labels to the vertical layout
    totalsLayout->addWidget(subtotalLabel);
    totalsLayout->addWidget(serviceChargeLabel);
    totalsLayout->addWidget(totalLabel);

    // Add the totals container to the right container
    rightContainer->addWidget(totalsContainer,0);

    totalsContainer->setStyleSheet("background-color: #222222; padding: 8px; border-radius: 8px;");

    // Buttons for reset and save order
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    resetButton = new QPushButton("Reset");
    connect(resetButton, &QPushButton::clicked, this, [this]() {
        orderItems.clear();     // Clear all ordered items
        updateOrderTable();     // Refresh the table and totals
    });

    saveButton = new QPushButton("Send Order");
    connect(saveButton, &QPushButton::clicked, this, &POS_AddOrder::sendOrder);

    // Set individual styles
    resetButton->setStyleSheet(R"(
        QPushButton {
            background-color: #6C6868;
            color: white;
            font-size: 16px;
            padding: 10px 20px;
            border-radius: 8px;
        }
        QPushButton:hover {
            background-color: #555555;
        }
    )");

    saveButton->setStyleSheet(R"(
        QPushButton {
            background-color: #491FFF;
            color: white;
            font-size: 16px;
            padding: 10px 20px;
            border-radius: 8px;
        }
        QPushButton:hover {
            background-color: #340DD8;
        }
    )");


    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(saveButton);
    rightContainer->addLayout(buttonLayout,4);

    // Combine both containers into the main layout
    mainLayout->addLayout(leftContainer, 3); // weight 3
    mainLayout->addLayout(rightContainer, 2); // weight 2


    // ========== QUERY 1: Fetching categories ==========
    if (db.transaction()) {
        QSqlQuery query(db);
        query.prepare("SELECT category_name FROM category ORDER BY display_order ASC");

        QPushButton *firstCategoryBtn = nullptr;

        if (query.exec()) {
            qDebug() << "Successfully accessed categories";

            while (query.next()) {
                QString categoryName = query.value(0).toString();

                QPushButton *btn = new QPushButton(categoryName);
                btn->setFixedSize(120, 40);
                btn->setCheckable(true);
                categoryLayout->addWidget(btn);
                categoryGroup->addButton(btn);

                btn->setStyleSheet(R"(
                QPushButton {
                    background-color: #000000;
                    color: white;
                    border-radius: 8px;
                }
                QPushButton:checked {
                    background-color: #0078d7;
                    color: white;
                    font-weight: bold;
                }
            )");

                connect(btn, &QPushButton::clicked, this, [=]() {
                    qDebug() << "Category clicked:" << categoryName;
                    loadItemsForCategory(categoryName);
                });

                if (!firstCategoryBtn) {
                    firstCategoryBtn = btn;
                }
            }

            if (firstCategoryBtn) {
                firstCategoryBtn->setChecked(true);
                emit firstCategoryBtn->clicked();
            }

            db.commit();
        } else {
            qDebug() << "Could not access categories";
            qDebug() << query.lastError();
            db.rollback();
        }
    } else {
        qDebug() << "Failed to start transaction for categories";
    }



    // ========== QUERY 2: Checking table status + generating order ID ==========
    if (db.transaction()) {
        QSqlQuery query_table(db);
        query_table.prepare("SELECT status, order_id FROM tables WHERE table_no = ?");
        query_table.addBindValue(table_no);

        qDebug() << "Running DB command to get status and order id";
        if (query_table.exec()) {
            while (query_table.next()) {
                table_status = query_table.value(0).toString();
                order_id = query_table.value(1).toString();
            }
            qDebug() << "Successfully accessed order id and table status";
        } else {
            qDebug() << query_table.lastError();
            db.rollback();
            return; // Don't continue if we can't even get table status
        }

        if (!order_id.isNull()) {
            qDebug() << "Just before the loadExistingOrderItems function";
            loadExistingOrderItems(order_id);
            qDebug() << "The table: " << table_no << " has order: " << order_id << " and the status is: " << table_status;
        } else {
            qDebug() << "The order is Null";
            qDebug() << "The table: " << table_no << " has order: " << order_id << " and the status is: " << table_status;

            QSqlQuery seq(db);
            seq.prepare("SELECT seq FROM sqlite_sequence WHERE name = 'orders'");
            if (seq.exec()) {
                while (seq.next()) {
                    int sequence = seq.value(0).toInt();
                    qDebug() << "The seq is " << sequence;
                    order_id = QString::number(sequence + 1);
                }
            } else {
                qDebug() << "The seq could not be fetched\n" << seq.lastError();
                db.rollback();
                return;
            }
        }


        db.commit();
    } else {
        qDebug() << "Failed to start transaction for table status + order_id";
    }

    orderInfoLabel->setText("Table No: " + table_no + "\n\nOrder ID: " + order_id);

    //Assigning value to member data functions
    m_orderId = order_id;
    m_tableNo = table_no;

}

void POS_AddOrder::loadExistingOrderItems(const QString &orderId)
{
    qDebug() << "inside the load existing order items function";
    QSqlQuery query(db);
    query.prepare(R"(
        SELECT m.item_name, m.menu_item_id, m.price, oi.quantity
        FROM order_items oi
        JOIN menu m ON oi.menu_item_id = m.menu_item_id
        WHERE oi.order_id = ?
    )");
    query.addBindValue(orderId);

    qDebug() << "Before the execution of query";
    if (!query.exec()) {
        qDebug() << "Failed to load existing order items:" << query.lastError();
        return;
    }
    qDebug() << "Successful execution of query";
    while (query.next()) {
        QString itemName = query.value(0).toString();
        int itemId = query.value(1).toInt();
        double price = query.value(2).toDouble();
        int quantity = query.value(3).toInt();

        qDebug() << "Accessed values as itemId: " << itemId << "quantity: "<< quantity << "price: " <<price;
        if (orderItems.contains(itemName)) {
            orderItems[itemName].quantity += quantity;
        } else {
            orderItems[itemName] = {itemId, quantity, price};
        }

    }

    qDebug() << "Before calling the update order table";
    updateOrderTable();
}


// Destructor
POS_AddOrder::~POS_AddOrder()
{
    delete ui;
}

// Adds an item to the order when a corresponding button is clicked
void POS_AddOrder::addItemToOrder()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    QString itemName = btn->property("itemName").toString();
    orderItems[itemName].quantity++;
    updateOrderTable();
}

// Updates the order table with current items and totals
void POS_AddOrder::updateOrderTable()
{
    qDebug() << "orderTable pointer:" << orderTable;
    if (!orderTable) {
        qDebug() << "Error: orderTable is nullptr!";
        return;
    }
    qDebug() << "inside the update order table function";
    orderTable->setRowCount(0);
    double total = 0;
    qDebug() << "before the for loop of the updateordertable function";
    for (auto it = orderItems.begin(); it != orderItems.end(); ++it) {

        int row = orderTable->rowCount();
        orderTable->insertRow(row);

        const QString &itemName = it.key();
        const OrderItem &item = it.value();

        double subtotal = item.price * item.quantity;
        total += subtotal;

        QTableWidgetItem *itemCell = new QTableWidgetItem(itemName);
        itemCell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        QTableWidgetItem *qtyCell = new QTableWidgetItem(QString::number(item.quantity));
        qtyCell->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *priceCell = new QTableWidgetItem(QString::number(subtotal));
        priceCell->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        QPushButton *deleteBtn = new QPushButton("Delete");
        deleteBtn->setProperty("itemName", itemName);
        deleteBtn->setStyleSheet("background-color: black; color: white; border-radius: 5px;");
        connect(deleteBtn, &QPushButton::clicked, this, &POS_AddOrder::decreaseItemQuantity);

        orderTable->setItem(row, 0, itemCell);
        orderTable->setItem(row, 1, qtyCell);
        orderTable->setItem(row, 2, priceCell);
        orderTable->setCellWidget(row, 3, deleteBtn);
        orderTable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    }

    qDebug() << "After the for loop of update order table function";
    qDebug() << "Total rows inserted in orderTable:" << orderTable->rowCount();

    double serviceCharge = 0.1 * total;
    double finalTotal = total + serviceCharge;

    subtotalLabel->setText("Subtotal:\tRs. " + QString::number(total));
    serviceChargeLabel->setText("Service Charge (10%) :\tRs. " + QString::number(serviceCharge));
    totalLabel->setText("<b>Total:\tRs. " + QString::number(finalTotal) + "</b>");
    qDebug() << "ending of the update order table function";
}

// Loads items belonging to the selected category
void POS_AddOrder::loadItemsForCategory(const QString &category)
{
    qDebug() << "Loading items for category:" << category;

    // Remove existing items from the grid
    QLayoutItem *item;
    while ((item = itemsLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QSqlQuery itemQuery(db);
    itemQuery.prepare("SELECT menu_item_id, item_name, price, image FROM menu WHERE category = :category");
    itemQuery.bindValue(":category", category.trimmed());

    if (!itemQuery.exec()) {
        qDebug() << "Failed to load items:" << itemQuery.lastError();
        return;
    }

    int index = 0;

    while (itemQuery.next()) {
        int id = itemQuery.value(0).toInt();
        QString itemName = itemQuery.value(1).toString();
        double price = itemQuery.value(2).toDouble();
        QByteArray imageData = itemQuery.value(3).toByteArray();

        QLabel *imageLabel = new QLabel;
        imageLabel->setFixedSize(100, 100);
        imageLabel->setAlignment(Qt::AlignCenter);

        QPixmap pixmap;
        if (pixmap.loadFromData(imageData)) {
            imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        } else {
            imageLabel->setText("No\nImage");
            imageLabel->setStyleSheet("color: gray; font-size: 10px;");
        }

        QLabel *nameLabel = new QLabel(itemName);
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->setWordWrap(true);
        nameLabel->setStyleSheet(R"(
            QLabel {
                color: white;
                font-size: 12px;
                font-weight: 600;
            }
        )");

        QFrame *card = new QFrame;
        card->setMinimumSize(120, 160);
        card->setMaximumSize(140, 180);
        card->setStyleSheet(R"(
            QFrame {
                background-color: transparent;
                border-radius: 10px;
            }
            QFrame:hover {
                background-color: #2b2b2b;
            }
        )");

        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setContentsMargins(8, 8, 8, 8);
        cardLayout->setSpacing(6);
        cardLayout->setAlignment(Qt::AlignCenter);
        cardLayout->addStretch();
        cardLayout->addWidget(imageLabel, 0, Qt::AlignCenter);
        cardLayout->addWidget(nameLabel);
        cardLayout->addStretch();

        card->setProperty("itemName", itemName);
        card->setProperty("price", price);
        card->setProperty("itemId", id);
        card->installEventFilter(this);

        int row = index / 5;
        int col = index % 5;
        itemsLayout->addWidget(card, row, col, Qt::AlignTop);
        ++index;
    }
}


void POS_AddOrder::sendOrder()
{
    qDebug() << "Send Order button clicked";
    qDebug() << "Sending order for Table:" << m_tableNo << "Order ID:" << m_orderId;

    // Early return if order is empty
    if (orderItems.isEmpty()) {
        QMessageBox::warning(this, "Empty Order", "Please add items before sending the order.");
        return;
    }


    //  Confirmation dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Send Order",
                                  "Are you sure you want to send this order?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes) {
        qDebug() << "User cancelled the order send.";
        return;  // Exit if user chooses No
    }


    bool orderExists = false;


    // Check if order already exists in orders table
    QSqlQuery checkOrder(db);
    checkOrder.prepare("SELECT COUNT(*) FROM orders WHERE order_id = ?");
    checkOrder.addBindValue(m_orderId);
    if (checkOrder.exec() && checkOrder.next()) {
        orderExists = (checkOrder.value(0).toInt() > 0);
    }

    if (!db.transaction()) {
        qDebug() << "Failed to start transaction: " << db.lastError();
        return;
    }
    bool success = true;

    if (!orderExists) {
        // 1. Insert into orders table
        QSqlQuery insertOrder(db);
        insertOrder.prepare("INSERT INTO orders(order_id, table_no, status, notes) VALUES (?, ?, ?,?)");
        insertOrder.addBindValue(m_orderId);
        insertOrder.addBindValue(m_tableNo);
        insertOrder.addBindValue("Preparing");
        insertOrder.addBindValue(notes);

        if (!insertOrder.exec()) {
            qDebug() << "Failed to insert into orders: " << insertOrder.lastError();
            success = false;
        }

        // 2. Update tables table with new order_id
        QSqlQuery updateTable(db);
        updateTable.prepare("UPDATE tables SET order_id = ? WHERE table_no = ?");
        updateTable.addBindValue(m_orderId);
        updateTable.addBindValue(m_tableNo);

        if (success && !updateTable.exec()) {
            qDebug() << "Failed to update table with order_id: " << updateTable.lastError();
            success = false;
        }

        QSqlQuery updateTableStatus(db);
        updateTableStatus.prepare("UPDATE tables SET status = 'occupied' WHERE table_no = ?");
        updateTableStatus.addBindValue(m_tableNo);

        if (success && !updateTableStatus.exec()) {
            qDebug() << "Failed to update table status: " << updateTableStatus.lastError();
            success = false;
        }


    } else {
        qDebug() << "Appending items to existing order";
    }

    // Delete old items
    if (success) {
        QSqlQuery deleteItems(db);
        deleteItems.prepare("DELETE FROM order_items WHERE order_id = ?");
        deleteItems.addBindValue(m_orderId);

        if (!deleteItems.exec()) {
            qDebug() << "Failed to delete old items: " << deleteItems.lastError();
            success = false;
        }
    }

    // Insert new order items
    if (success) {
        for (auto it = orderItems.begin(); it != orderItems.end(); ++it) {
            const OrderItem &item = it.value();

            QSqlQuery insertItem(db);
            insertItem.prepare("INSERT INTO order_items (order_id, menu_item_id, quantity) VALUES (?, ?, ?)");
            insertItem.addBindValue(m_orderId);
            insertItem.addBindValue(item.id);
            insertItem.addBindValue(item.quantity);

            if (!insertItem.exec()) {
                qDebug() << "Failed to insert item: " << insertItem.lastError();
                success = false;
                break;
            }
        }
    }

    // Update order status
    if (success) {
        QSqlQuery updateStatus(db);
        updateStatus.prepare("UPDATE orders SET status = 'Preparing' WHERE order_id = ?");
        updateStatus.addBindValue(m_orderId);
        if (!updateStatus.exec()) {
            qDebug() << "Failed to update order status: " << updateStatus.lastError();
            success = false;
        }
    }


    // Commit or rollback
    if (success) {
        if (!db.commit()) {
            qDebug() << "Failed to commit transaction: " << db.lastError();
            db.rollback();
            return;
        }
    } else {
        db.rollback();
        return;
    }

    // Final UI updates after successful submission
    QMessageBox::information(this, "Order Sent", "The order has been successfully sent to the kitchen.");
    orderItems.clear();
    updateOrderTable();

    // Close previous windows if they exist
    if (m_posWindow) {
        m_posWindow->close();
    }
    if (m_mainWindow) {
        m_mainWindow->close();
    }

    // Launch a new main window
    MainWindow *mainWin = new MainWindow();
    mainWin->show();

    // Close this order window
    this->close();

}

// Decreases the quantity of an item or removes it from the order
void POS_AddOrder::decreaseItemQuantity()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    QString itemName = btn->property("itemName").toString();

    if (orderItems.contains(itemName)) {
        if (orderItems[itemName].quantity > 1) {
            orderItems[itemName].quantity--;
        } else {
            orderItems.remove(itemName);
        }
        updateOrderTable();
    }
}

// Event filter to detect clicks on item cards
bool POS_AddOrder::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QString itemName = watched->property("itemName").toString();
        double price = watched->property("price").toDouble();
        int id = watched->property("itemId").toInt();

        if (!itemName.isEmpty()) {
            if (!orderItems.contains(itemName)) {
                orderItems[itemName] = {id, 1, price};
            } else {
                orderItems[itemName].quantity++;
            }
            updateOrderTable();
        }
        return true;
    }
    return QWidget::eventFilter(watched, event);
}

void POS_AddOrder::onAddNotesClicked()
{
    bool ok;
    QString text = QInputDialog::getMultiLineText(this, "Add Notes",
                                                  "Enter notes:",
                                                  notes,  // prefill with existing notes if any
                                                  &ok);
    if (ok) {
        notes = text;  // Save the entered notes in the member variable
        QMessageBox::information(this, "Notes Saved", "Notes have been saved.");
    }
}
