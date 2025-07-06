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
    if(queryTables.exec("SELECT * FROM tables")){
         qDebug()<<"Accessed tables from database";
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
