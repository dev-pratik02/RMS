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
    orderTable = new QTableWidget(0, 3);
    orderTable->setHorizontalHeaderLabels({"Item", "No.", "Price"});
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
    orderItems[itemName]++;
    updateOrderTable();
}

void POS_AddOrder::updateOrderTable()
{
    orderTable->setRowCount(0);
    double total = 0;

    for (auto it = orderItems.begin(); it != orderItems.end(); ++it) {
        int row = orderTable->rowCount();
        orderTable->insertRow(row);

        orderTable->setItem(row, 0, new QTableWidgetItem(it.key()));
        orderTable->setItem(row, 1, new QTableWidgetItem(QString::number(it.value())));
        double price = 120; // Static price for now
        orderTable->setItem(row, 2, new QTableWidgetItem(QString::number(price * it.value())));

        total += price * it.value();
    }

    orderInfoLabel->setText("Table No: 01\nOrder ID: 10745\nTotal: Rs. " + QString::number(total));
}


void POS_AddOrder::loadItemsForCategory(const QString &category) {
    qDebug() << "load items function:";

    if (!itemsLayout) {
        qDebug() << "itemsLayout is not initialized!";
        return;
    }

    // Clear layout safely
    QLayoutItem *item;
    while ((item = itemsLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QSqlQuery itemQuery(db);
    itemQuery.prepare("SELECT item_name, price, image FROM menu WHERE category = :category");
    itemQuery.bindValue(":category", category.trimmed());

    if (itemQuery.exec()) {
        int index = 0;
        qDebug() << "executed the query";
        qDebug() << "Loading items for category:" << category;

        while (itemQuery.next()) {
            qDebug() << "inside the while loop";
            QString itemName = itemQuery.value(0).toString();
            double price = itemQuery.value(1).toDouble();
            QByteArray imagePath = itemQuery.value(2).toByteArray();
            QPixmap pixmap;
            if (pixmap.loadFromData(imagePath)) {
                QLabel *imageLabel = new QLabel;
                imageLabel->setPixmap(pixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                itemsLayout->addWidget(imageLabel);
            } else {
                qDebug() << "Failed to load pixmap from database BLOB";
            }
            QPushButton *itemBtn = new QPushButton();
            itemBtn->setIcon(QIcon(imagePath));
            itemBtn->setIconSize(QSize(100, 100));
            itemBtn->setFixedSize(120, 120);
            itemBtn->setProperty("itemName", itemName);
            itemBtn->setProperty("price", price);

            connect(itemBtn, &QPushButton::clicked, this, &POS_AddOrder::addItemToOrder);

            itemsLayout->addWidget(itemBtn, index / 5, index % 5);
            ++index;
        }
    } else {
        qDebug() << "Failed to load items: " << itemQuery.lastError();
    }
}
