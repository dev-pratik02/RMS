#include "table.h"
#include "ui_table.h"
#include<edit.h>

table::table(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::table)
    , editpage(nullptr)
{
    ui->setupUi(this);
    connect(ui->btn_edit, &QPushButton::clicked, this, &table::on_btn_edit_clicked);


    // Only add the database if it doesn't already exist
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("/Users/pratik/Programming/RMS/RmsApp.db");
    } else {
        mydb = QSqlDatabase::database("qt_sql_default_connection");
    }

    if(mydb.open()){
        qDebug() <<"Database is accessed by tables page";
    }
    else{
        qDebug() << "Database connection failed" ;
        qDebug() << "Error:"<< mydb.lastError();
    }
    QSqlQuery queryTables(mydb);
    queryTables.prepare("SELECT * FROM tables");
    if (queryTables.exec()) {
        qDebug() << "Accessed tables from database";

        int row = 0;
        QStringList headers= {"Table no.","Seats","Status","Order Id","Timestamp","Remarks"};

        ui->table_tables->setColumnCount(6);
        ui->table_tables->setHorizontalHeaderLabels(headers);
        while (queryTables.next()) {

            ui->table_tables->insertRow(row); //entry of empty row

            for (int col = 0; col < queryTables.record().count(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(queryTables.value(col).toString());
                item->setTextAlignment(Qt::AlignCenter);  // ← Center-align the text
                ui->table_tables->setItem(row, col, item);
            }
            row++;
        }
        QSqlQuery queryAvailableTables(mydb);
        queryAvailableTables.prepare("SELECT * FROM tables where status='free'");
        int count=0;
        if(queryAvailableTables.exec()){
            while(queryAvailableTables.next()){
                count++;
            }
        }
        ui->totalTables->setText("Total no. of tables: "+ QString::number(row).trimmed() );
        ui->totalTables->setAlignment(Qt::AlignCenter);
        ui->availableTables->setText("Available tables: "+ QString::number(count).trimmed() );
        ui->availableTables->setAlignment(Qt::AlignCenter);

    }

    else {
        qDebug() << "Could not access tables";
        qDebug() << queryTables.lastError();
    }
}

table::~table()
{
    delete ui;
}
void table::on_btn_edit_clicked()
{
    this->hide();
    if (!editpage) {
        editpage = new edit(this);
    }

    editpage->show();
}
