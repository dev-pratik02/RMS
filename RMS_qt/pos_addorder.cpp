#include "pos_addorder.h"
#include "ui_pos_addorder.h"

// Constructor for POS_AddOrder
POS_AddOrder::POS_AddOrder(QString table_no, QWidget *parent)
    : QWidget(parent), ui(nullptr)
{
    // Set window title and size
    setWindowTitle("POS - Add Order");
    setMinimumSize(1280, 800);
    resize(1280, 800);
    qDebug() << "The received table no. is " << table_no;

    // Setup database connection
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/Users/pratik/Programming/RMS/RMS_qt/RmsApp.db");
    } else {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }

    // Open database and check status
    if (db.open()) {
        qDebug() << "Database connected successfully by POS";
    } else {
        qDebug() << db.lastError();
    }

    // Query the table's current status and order_id
    QSqlQuery query_table(db);
    QString table_status, order_id;
    query_table.prepare("SELECT status,order_id from tables where table_no = ?");
    query_table.addBindValue(table_no);

    if (query_table.exec()) {
        while (query_table.next()) {
            table_status = query_table.value(0).toString();
            order_id = query_table.value(1).toString();
        }
    } else {
        qDebug() << query_table.lastError();
    }


    //checking if the table currently has any orders or not
    if(!order_id.isNull()){
        qDebug() << "The table: " << table_no << "has order: " <<order_id << "and the status is: " << table_status;
    }
    else{
        qDebug() << "The order is Null";
        qDebug() << "The table: " << table_no << "has order: " <<order_id << "and the status is: " << table_status;

        QSqlQuery seq(db);
        seq.prepare("SELECT seq from sqlite_sequence where name= 'orders'");
        if(seq.exec()){
            while(seq.next()){
                int sequence= seq.value(0).toInt();
                qDebug() << "the seq is " << sequence;
                order_id = QString::number(sequence+1);
            }
        }
        else{
            qDebug() << "the seq could not be fetched \n " << seq.lastError();
        }
    }

    //Assigning value to member data functions
    m_orderId = order_id;
    m_tableNo = table_no;

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

    // Fetch categories from the database
    QSqlQuery query(db);
    query.prepare("SELECT category_name FROM category ORDER BY display_order ASC");

    QPushButton *firstCategoryBtn = nullptr;

    if (query.exec()) {
        qDebug() << "Successfully accessed categories";

        while (query.next()) {
            QString categoryName = query.value(0).toString();

            // Create button for each category
            QPushButton *btn = new QPushButton(categoryName);
            btn->setFixedSize(120, 40);
            btn->setCheckable(true);
            categoryLayout->addWidget(btn);
            categoryGroup->addButton(btn);

            // Set category button styles
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

            // Connect category button click to item loading
            connect(btn, &QPushButton::clicked, this, [=]() {
                qDebug() << "Category clicked:" << categoryName;
                loadItemsForCategory(categoryName);
            });

            // Remember the first button for default selection
            if (!firstCategoryBtn) {
                firstCategoryBtn = btn;
            }
        }

        // Auto-select and load first category
        if (firstCategoryBtn) {
            firstCategoryBtn->setChecked(true);
            emit firstCategoryBtn->clicked();
        }
    } else {
        qDebug() << "Could not access categories";
        qDebug() << query.lastError();
    }

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
    orderInfoLabel = new QLabel("Table No: " + table_no + "\n\nOrder ID: " + order_id);
    orderInfoLabel->setStyleSheet(R"(
        font-size: 14px;
        font-weight: bold;
        padding: 6px;
        margin-bottom: 15px;
    )");
    rightContainer->addWidget(orderInfoLabel,0);

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
    orderTable->setRowCount(0);
    double total = 0;

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

    double serviceCharge = 0.1 * total;
    double finalTotal = total + serviceCharge;

    subtotalLabel->setText("Subtotal:\tRs. " + QString::number(total));
    serviceChargeLabel->setText("Service Charge (10%) :\tRs. " + QString::number(serviceCharge));
    totalLabel->setText("<b>Total:\tRs. " + QString::number(finalTotal) + "</b>");
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


    QSqlQuery updateTables(db);
    updateTables.prepare("UPDATE tables set order_id = ?");
    updateTables.addBindValue(m_orderId);

    if(updateTables.exec()){
        qDebug() << "Added order_id in tables after clicking send button";
    }
    else {
        qDebug() << "could not update order id in  tables \n " << updateTables.lastError();
    }


    QSqlQuery updateOrders(db);
    updateOrders.prepare("INSERT INTO orders(table_no,order_id) VALUES('?','?')");
    updateOrders.addBindValue(m_tableNo);
    updateOrders.addBindValue(m_orderId);

    if(updateOrders.exec()){
        qDebug() << "Added new orders record after clicking send button";
    }
    else{
        qDebug() << "Could not insert new order record \n " << updateOrders.lastError();
    }

    // Iterate over orderItems
    for (auto it = orderItems.begin(); it != orderItems.end(); ++it) {
        const QString &itemName = it.key();
        const OrderItem &item = it.value();

        int menuItemId = item.id;
        int quantity = item.quantity;
        double unit_price = item.price;

        qDebug() << "ID:" << menuItemId << ", Item:" << itemName << ", Qty:" << quantity << ", Price:" << unit_price;

        // Use these to insert into DB or send to server

        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO order_items (order_id, menu_item_id, quantity) VALUES (?, ?, ?)");
        insertQuery.addBindValue(m_orderId);
        insertQuery.addBindValue(menuItemId);
        insertQuery.addBindValue(quantity);
        if (insertQuery.exec()) {
            qDebug() << "Insertion completed successfully";
        }
        else{
            qDebug() << "Insert failed:" << insertQuery.lastError();
            return;
        }
    }

    QSqlQuery updateQuery(db);
    updateQuery.prepare("UPDATE orders set status = 'Preparing' where order_id = ?");
    updateQuery.addBindValue(m_orderId);
    if(updateQuery.exec()){
        qDebug() << "updated orders successfully; set new status";
    }
    else {
        qDebug() << "Could not change order status: \n" << updateQuery.lastError();
    }
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
