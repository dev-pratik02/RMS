#include "pos.h"
#include "ui_pos.h"

pos::pos(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pos)
{
    ui->setupUi(this);

    // Only add the database if it doesn't already exist
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("/Users/pratik/Programming/RMS/RMS_qt/RmsApp.db");
    } else {
        mydb = QSqlDatabase::database("qt_sql_default_connection");
    }

    if(mydb.open()){
        qDebug() <<"Database is connected by orders page";
    }
    else{
        qDebug() << "Database connection failed" ;
        qDebug() << "Error:"<< mydb.lastError();
    }

    QSqlQuery query(mydb);
    query.prepare("SELECT * FROM tables");
    int row = 0;
    if(query.exec()){
        qDebug() << "Successfully accessed tables";
        while(query.next()){
            row++;
        }
        qDebug() << "No. of tables: " << row;
    }
    else {
        qDebug() << "Could not access tables";
    }

    QStringList table_list;

    for(int i=1;i<=row;i++){
        QString temp = QString::number(i);
        table_list.append(temp);
    }
    ui->pos_table_dropdown->addItems(table_list);
}

pos::~pos()
{
    delete ui;
}

void pos::on_btn_place_order_clicked()
{

}

