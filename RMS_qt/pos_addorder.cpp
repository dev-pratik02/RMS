#include "pos_addorder.h"



POS_AddOrder::POS_AddOrder(QString table_no,QWidget *parent)
    : QWidget(parent),
    ui(nullptr)
{
    setWindowTitle("POS - Add Order");
    setMinimumSize(1280, 800);
    resize(1280, 800);
    qDebug() << "The received table no. is " << table_no;

    //DB connection;
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/Users/pratik/Programming/RMS/RMS_qt/RmsApp.db");
    } else {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    if(db.open()){
        qDebug() << "Database connected successfully by POS";
    }
    else{
        qDebug() << db.lastError();
    }

    //db table status check
    QSqlQuery query_table(db);
    QString table_status, order_id;
    query_table.prepare("SELECT status,order_id from tables where table_no = ?");
    query_table.addBindValue(table_no);
    if(query_table.exec()){
        while(query_table.next()){
            table_status = query_table.value(0).toString();
            order_id= query_table.value(1).toString();
        }

        if(order_id.isEmpty()){
            qDebug() << "Null";

        }
    }
    else {
        qDebug() << query_table.lastError();
    }
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // ==========================
    // LEFT CONTAINER
    // ==========================
    QVBoxLayout *leftContainer = new QVBoxLayout();


    // Items layout MUST be created BEFORE you call loadItemsForCategory()
    QWidget *itemsWidget = new QWidget();
    itemsLayout = new QGridLayout(itemsWidget);  // << This is key

    // Category Scroll Area
    // Horizontal Scrollable Category Bar
    QWidget *categoryWidget = new QWidget();
    QHBoxLayout *categoryLayout = new QHBoxLayout(categoryWidget);

    QButtonGroup *categoryGroup = new QButtonGroup(this);
    categoryGroup->setExclusive(true);

    QSqlQuery query(db);
    query.prepare("SELECT category_name FROM category ORDER BY display_order ASC");

    QString category;
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
                firstCategoryBtn = btn;  // store the first button
            }
        }

        // Auto-select first category
        if (firstCategoryBtn) {
            firstCategoryBtn->setChecked(true);
            emit firstCategoryBtn->clicked();  // triggers loading of items
        }

    } else {
        qDebug() << "Could not access categories";
        qDebug() << query.lastError();
    }




    QScrollArea *categoryScroll = new QScrollArea();
    categoryScroll->setWidgetResizable(true);
    categoryScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    categoryScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    categoryScroll->setFixedHeight(60);
    categoryScroll->setWidget(categoryWidget);


    // Items Scroll Area

    QScrollArea *itemsScroll = new QScrollArea();
    itemsScroll->setWidgetResizable(true);
    itemsScroll->setWidget(itemsWidget);

    leftContainer->addWidget(categoryScroll);
    leftContainer->addWidget(itemsScroll);

    // ==========================
    // RIGHT CONTAINER
    // ==========================
    QVBoxLayout *rightContainer = new QVBoxLayout();

    // ---------------------------
    // Order Info Header
    // ---------------------------
    orderInfoLabel = new QLabel("Table No: " + table_no + "\n\nOrder ID: " + order_id);
    orderInfoLabel->setStyleSheet(R"(
        font-size: 14px;
        font-weight: bold;
        padding: 6px;
        margin-bottom: 15px;
    )");
    rightContainer->addWidget(orderInfoLabel);

    // ---------------------------
    // Order List Scroll Area (custom, replaces QTableWidget)
    // ---------------------------
    // ---------------------------
    // Order Table Setup
    // ---------------------------
    orderTable = new QTableWidget(0, 4, this);
    orderTable->setHorizontalHeaderLabels({"Item", "No.", "Price", "Action"});

    // Resize policy
    orderTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    orderTable->verticalHeader()->setVisible(false);
    orderTable->setShowGrid(false);
    orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    orderTable->setSelectionMode(QAbstractItemView::NoSelection);
    orderTable->setFocusPolicy(Qt::NoFocus);
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
        }
        QTableWidget::item {
            padding: 8px;
            background-color: transparent;
        }

        QTableWidget::item:selected {
            background-color: #444444;
        }
    )");

    orderTable->setFixedHeight(300);  // or setSizePolicy if dynamic is needed
    orderTable->verticalHeader()->setDefaultSectionSize(40);  // Fixed row height

    rightContainer->addWidget(orderTable);


    // ---------------------------
    // Subtotal, Service Charge, Total
    // ---------------------------
    subtotalLabel = new QLabel("Subtotal:\tRs. 0");
    serviceChargeLabel = new QLabel("Service Charge:\tRs. 0");
    totalLabel = new QLabel("<b>Total:\tRs. 0</b>");
    subtotalLabel->setStyleSheet("font-size: 16px; margin-bottom: 2px;");
    serviceChargeLabel->setStyleSheet("font-size: 12px; margin-bottom: 2px;");
    totalLabel->setStyleSheet("font-size: 20px; font-weight:bold; margin-bottom: 6px;");

    rightContainer->addWidget(subtotalLabel);
    rightContainer->addWidget(serviceChargeLabel);
    rightContainer->addWidget(totalLabel);


    // Bottom: Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    resetButton = new QPushButton("Reset");
    saveButton = new QPushButton("Send Order");
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(saveButton);
    rightContainer->addLayout(buttonLayout);

    // Add to main layout
    mainLayout->addLayout(leftContainer, 3);
    mainLayout->addLayout(rightContainer, 2);
}

POS_AddOrder::~POS_AddOrder()
{
    delete ui;
}

void POS_AddOrder::addItemToOrder()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    QString itemName = btn->property("itemName").toString();
    orderItems[itemName].quantity++;

    updateOrderTable();
}

void POS_AddOrder::updateOrderTable()
{
    orderTable->setRowCount(0);  // Clear previous table rows
    double total = 0;

    for (auto it = orderItems.begin(); it != orderItems.end(); ++it) {
        int row = orderTable->rowCount();
        orderTable->insertRow(row);

        const QString &itemName = it.key();
        const OrderItem &item = it.value();

        double subtotal = item.price * item.quantity;
        total += subtotal;

        // Column 0: Item name
        QTableWidgetItem *itemCell = new QTableWidgetItem(itemName);
        itemCell->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        // Column 1: Quantity
        QTableWidgetItem *qtyCell = new QTableWidgetItem(QString::number(item.quantity));
        qtyCell->setTextAlignment(Qt::AlignCenter);

        // Column 2: Price
        QTableWidgetItem *priceCell = new QTableWidgetItem(QString::number(subtotal));
        priceCell->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        // Column 3: Delete button
        QPushButton *deleteBtn = new QPushButton("Delete");
        deleteBtn->setProperty("itemName", itemName);
        deleteBtn->setStyleSheet("background-color: black; color: white; border-radius: 5px;");
        connect(deleteBtn, &QPushButton::clicked, this, &POS_AddOrder::decreaseItemQuantity);

        // Add items to table
        orderTable->setItem(row, 0, itemCell);
        orderTable->setItem(row, 1, qtyCell);
        orderTable->setItem(row, 2, priceCell);
        orderTable->setCellWidget(row, 3, deleteBtn);
    }

    double serviceCharge = 100;
    double finalTotal = total + serviceCharge;

    subtotalLabel->setText("Subtotal:\tRs. " + QString::number(total));
    serviceChargeLabel->setText("Service Charge:\tRs. " + QString::number(serviceCharge));
    totalLabel->setText("<b>Total:\tRs. " + QString::number(finalTotal) + "</b>");
}



void POS_AddOrder::loadItemsForCategory(const QString &category) {
    qDebug() << "Loading items for category:" << category;

    // Clear previous layout
    QLayoutItem *item;
    while ((item = itemsLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QSqlQuery itemQuery(db);
    itemQuery.prepare("SELECT item_name, price, image FROM menu WHERE category = :category");
    itemQuery.bindValue(":category", category.trimmed());

    if (!itemQuery.exec()) {
        qDebug() << "Failed to load items:" << itemQuery.lastError();
        return;
    }

    int index = 0;

    while (itemQuery.next()) {
        QString itemName = itemQuery.value(0).toString();
        double price = itemQuery.value(1).toDouble();
        QByteArray imageData = itemQuery.value(2).toByteArray();

        // Image
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

        // Name label (no border or padding)
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

        // Card container
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

        // Make clickable
        card->setProperty("itemName", itemName);
        card->setProperty("price", price);
        card->installEventFilter(this);

        // Add to grid
        int row = index / 5;
        int col = index % 5;
        itemsLayout->addWidget(card, row, col, Qt::AlignTop);
        ++index;
    }
}


bool POS_AddOrder::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QString itemName = watched->property("itemName").toString();
        double price = watched->property("price").toDouble();  // new line

        if (!itemName.isEmpty()) {
            if (!orderItems.contains(itemName)) {
                orderItems[itemName] = {1, price};
            } else {
                orderItems[itemName].quantity++;
            }
            updateOrderTable();
        }
        return true;
    }
    return QWidget::eventFilter(watched, event);
}

void POS_AddOrder::decreaseItemQuantity()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    QString itemName = btn->property("itemName").toString();

    if (orderItems.contains(itemName)) {
        if (orderItems[itemName].quantity > 1) {
            orderItems[itemName].quantity--;
        } else {
            orderItems.remove(itemName);  // Remove item entirely if quantity hits 0
        }
        updateOrderTable();
    }
}

