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

    // Top: Order Info
    orderInfoLabel = new QLabel("Table No: "+table_no+"\nOrder ID: "+"\n");
    orderInfoLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    rightContainer->addWidget(orderInfoLabel);

    // Middle: Order Table
    orderTable = new QTableWidget(0, 4);
    orderTable->setHorizontalHeaderLabels({"Item", "No.", "Price", ""});

    orderTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    rightContainer->addWidget(orderTable);

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
    orderTable->setRowCount(0);
    double total = 0;

    for (auto it = orderItems.begin(); it != orderItems.end(); ++it) {
        int row = orderTable->rowCount();
        orderTable->insertRow(row);

        const QString &itemName = it.key();
        const OrderItem &item = it.value();

        // Column 0: Item name
        orderTable->setItem(row, 0, new QTableWidgetItem(itemName));

        // Column 1: Quantity
        orderTable->setItem(row, 1, new QTableWidgetItem(QString::number(item.quantity)));

        // Column 2: Price (subtotal)
        double subtotal = item.price * item.quantity;
        orderTable->setItem(row, 2, new QTableWidgetItem(QString::number(subtotal)));

        // Column 3: Decrease (-) button
        QPushButton *minusBtn = new QPushButton("Delete");
        minusBtn->setStyleSheet("font-weight: bold; background-color: #000000; color: white; border-radius: 5px;");
        orderTable->setCellWidget(row, 3, minusBtn);

        // Store item name in button
        minusBtn->setProperty("itemName", itemName);

        connect(minusBtn, &QPushButton::clicked, this, &POS_AddOrder::decreaseItemQuantity);

        total += subtotal;
    }

    orderInfoLabel->setText("Table No: 01\nOrder ID: 10745\nTotal: Rs. " + QString::number(total));
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

