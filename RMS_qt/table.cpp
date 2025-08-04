#include "table.h"
#include "ui_table.h"
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include "databasemanager.h"
#include "globals.h"
table::table(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::table)
    , editPage(nullptr)
{
    ui->setupUi(this);



    QSqlDatabase &db = DatabaseManager::getDatabase();
    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
    } else {
        qDebug() << "Database connected!";
    }

    loadTableList();

    if(g_userRole != "Manager" && g_userRole != "Admin"){
        ui->btn_edit->setVisible(false);
    }

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
    ui->table_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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

    QSqlQuery totalQuery(db);
    totalQuery.prepare("SELECT COUNT(*) FROM tables");
    if(totalQuery.exec()){
        if (totalQuery.next()) {
            totalTables = totalQuery.value(0).toInt();
            ui->total->setText("Total Tables: " + QString::number(totalTables));
        }
    }
    else{
        qDebug() << "could not execute the query \n " << totalQuery.lastError();
    }

    QSqlQuery availableQuery(db);
    availableQuery.prepare("SELECT COUNT(*) FROM tables WHERE status = 'available'");
    if(availableQuery.exec()){
        if (availableQuery.next()) {
            availableTables = availableQuery.value(0).toInt();
            ui->available->setText("Available Tables: " + QString::number(availableTables));
        }
    }
    else{
        qDebug() << "could not execute the query \n " << availableQuery.lastError();
    }

    loadTableList();
    updateSeatLabels();



}
void table::updateSeatLabels()
{
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*), SUM(CASE WHEN status = 'available' THEN 1 ELSE 0 END) FROM tables");
    if(query.exec()){
        if (query.next()) {
            int Total = query.value(0).toInt();
            int Available = query.value(1).toInt();

            ui->total->setText("Total Tables: " + QString::number(Total));
            ui->available->setText("Available Tables: " + QString::number(Available));
        }
    }
    else {
        qDebug() << "Failed to query table counts:" << query.lastError().text();
    }
}
void table::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event); // Call base class
    refreshTableList(); // Refresh table and labels when this window is shown
}

