#include "table.h"
#include "ui_table.h"
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include "databasemanager.h"

table::table(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::table)
    , editPage(nullptr)
{
    ui->setupUi(this);

    ui->total->setStyleSheet("background-color: rgb(0,102,204); color: rgb(255,255,255); padding: 4px; border-radius: 5px;");



    QSqlDatabase db = DatabaseManager::getDatabase();


    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
    } else {
        qDebug() << "Database connected!";
    }

    loadTableList();

    // connect(ui->btn_edit, &QPushButton::clicked, this, &table::on_btn_edit_clicked);
}

table::~table()
{
    delete ui;
}

void table::loadTableList()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM tables");

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

    int totalTables = 0;
    int availableTables = 0;

    QSqlQuery totalQuery("SELECT COUNT(*) FROM tables");
    if (totalQuery.next()) {
        totalTables = totalQuery.value(0).toInt();
        ui->label_t->setText(QString::number(totalTables));
    }

    QSqlQuery availableQuery("SELECT COUNT(*) FROM tables WHERE status = 'available'");
    if (availableQuery.next()) {
        availableTables = availableQuery.value(0).toInt();
        ui->label_a->setText(QString::number(availableTables));
    }

    //  Only if available = 0, turn label red
    if (availableTables == 0) {
        ui->available->setStyleSheet("background-color: rgb(220,20,60); color: rgb(255,255,255);font: 700 12pt Arial; padding: 4px; border-radius: 5px;");
    } else {
        ui->available->setStyleSheet("background-color: rgb(0,208,0); color: rgb(255,255,255);font: 700 12pt Arial; padding: 4px; border-radius: 5px;");
    }




    loadTableList();
    updateSeatLabels();



}
void table::updateSeatLabels()
{
    QSqlQuery query("SELECT COUNT(*), SUM(CASE WHEN status = 'available' THEN 1 ELSE 0 END) FROM tables");

    if (query.next()) {
        int Total = query.value(0).toInt();
        int Available = query.value(1).toInt();

        ui->label_t->setText(QString::number(Total));
        ui->label_a->setText(QString::number(Available));
    } else {
        qDebug() << "Failed to query table counts:" << query.lastError().text();
    }
}
void table::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event); // Call base class
    refreshTableList(); // Refresh table and labels when this window is shown
}

