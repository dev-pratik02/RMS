#include "pos_addorder.h"


POS_AddOrder::POS_AddOrder(QWidget *parent)
    : QWidget(parent),
    ui(nullptr)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

}

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

    // Category Scroll Area
    // Horizontal Scrollable Category Bar
    QWidget *categoryWidget = new QWidget();
    QHBoxLayout *categoryLayout = new QHBoxLayout(categoryWidget);

    QButtonGroup *categoryGroup = new QButtonGroup(this);
    categoryGroup->setExclusive(true);

    QSqlQuery query(db);
    query.prepare("SELECT category_name FROM category ORDER BY display_order ASC");

    QString category;
    if (query.exec()) {
        qDebug() << "Successfully accessed categories";
        while (query.next()) {
            category = query.value(0).toString();

            QPushButton *btn = new QPushButton(category);
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

            // Later: filter items grid based on selected category
            connect(btn, &QPushButton::clicked, this, [category]() {
                qDebug() << "Category clicked:" << category;
            });
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
    QWidget *itemsWidget = new QWidget();
    itemsLayout = new QGridLayout(itemsWidget);

    for (int i = 0; i < 100; ++i) {
        QPushButton *itemBtn = new QPushButton();
        itemBtn->setIcon(QIcon(":/images/burger.png"));
        itemBtn->setIconSize(QSize(100, 100));
        itemBtn->setFixedSize(120, 120);
        itemBtn->setProperty("itemName", "Burger");
        connect(itemBtn, &QPushButton::clicked, this, &POS_AddOrder::addItemToOrder);
        itemsLayout->addWidget(itemBtn, i / 5, i % 5);
    }

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
