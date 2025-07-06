#include "edit.h"
#include "ui_edit.h"
#include<add_tables.h>
edit::edit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit)
{
    ui->setupUi(this);
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
    QSqlQuery queryEditTables(mydb);
    queryEditTables.prepare("SELECT * FROM table_assign");
    if (queryEditTables.exec()) {
        qDebug() << "Accessed tables from database";

        int row = 0;
        QStringList headers= {"Table no.","Seats","Table type","Location","Description"};

        ui->table_editTables->setColumnCount(5);
        ui->table_editTables->setHorizontalHeaderLabels(headers);
        while (queryEditTables.next()) {

            ui->table_editTables->insertRow(row); //entry of empty row

            for (int col = 0; col < queryEditTables.record().count(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(queryEditTables.value(col).toString());
                item->setTextAlignment(Qt::AlignCenter);  // ← Center-align the text
                ui->table_editTables->setItem(row, col, item);
            }
            row++;
        }

    }

    else {
        qDebug() << "Could not access tables";
        qDebug() << queryEditTables.lastError();
    }

}

edit::~edit()
{
    delete ui;
}

void edit::on_btn_back_clicked()
{
    this->hide(); // Hide current
    parentWidget()->show();


}
void edit::on_btn_add_clicked()
{
    add_tables *addPage = new add_tables(this);  // 👈 Pass 'this' (pointer to edit page)
    addPage->show();
    this->hide();  // Optional
}
