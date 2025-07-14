#include "table.h"
#include "ui_table.h"
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

table::table(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::table)
    , editPage(nullptr)
{
    ui->setupUi(this);

    // Setup SQLite connection
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbPath = "C:/Users/LENOVO/OneDrive/Desktop/database/rms_app.db";
    qDebug() << "Trying to open DB at path:" << dbPath;
    db.setDatabaseName(dbPath);


    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
    } else {
        qDebug() << "Database connected!";
    }

    loadTableList();

    connect(ui->btn_edit, &QPushButton::clicked, this, &table::on_btn_edit_clicked);
}

table::~table()
{
    delete ui;
}

void table::loadTableList()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM table_list");

    if (model->lastError().isValid()) {
        qDebug() << "Error loading table_list:" << model->lastError().text();
        return;
    }

    ui->table_list->setModel(model);
    ui->table_list->resizeColumnsToContents();
    ui->table_list->setColumnWidth(0, 80);   // Table No
    ui->table_list->setColumnWidth(1, 60);   // Seats
    ui->table_list->setColumnWidth(2, 100);  // Location
    ui->table_list->setColumnWidth(3, 100);  // Orientation
    ui->table_list->setColumnWidth(4, 100);  // Quality
    ui->table_list->setColumnWidth(5, 200);  // Description
    ui->table_list->setColumnWidth(6, 100);
}

void table::on_btn_edit_clicked()
{
    this->hide();
    if (!editPage) {
        editPage = new edit(this);
    }
    editPage->show();
}
void table::refreshTableList()
{
    loadTableList();
    updateSeatLabels();

}
void table::updateSeatLabels()
{
    QSqlQuery query("SELECT COUNT(*), SUM(CASE WHEN status = 'Available' THEN 1 ELSE 0 END) FROM table_list");

    if (query.next()) {
        int Total = query.value(0).toInt();
        int Available = query.value(1).toInt();

        ui->label_3->setText(QString::number(Total));
        ui->available_2->setText(QString::number(Available));
    } else {
        qDebug() << "Failed to query table counts:" << query.lastError().text();
    }
}
void table::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event); // Call base class
    refreshTableList(); // Refresh table and labels when this window is shown
}

