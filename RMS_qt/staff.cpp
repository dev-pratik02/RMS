#include "staff.h"
#include "ui_staff.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

staff::staff(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::staff)
{
    ui->setupUi(this);

    qDebug() << "The application dir path is :\n" << QCoreApplication::applicationDirPath();

    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        QString dbPath = "C:/Users/VICTUS/OneDrive/Desktop/database/staff.db";
        mydb.setDatabaseName(dbPath);
    } else {
        mydb = QSqlDatabase::database("qt_sql_default_connection");
    }
    if (mydb.open()) {
        qDebug() << "Database is accessed by staff page";
    }
    else {
        qDebug() << "Database connection failed";
        qDebug() << "Error:" << mydb.lastError();
    }

    loadStaffData();
}



staff::~staff()
{
    delete ui;
}

void staff::loadStaffData()
{
    ui->table_staff->setRowCount(0); // clear existing rows

    QSqlQuery query(mydb);
    if (!query.exec("SELECT staff_id, staff_name, position, salary, age, contact FROM staff")) {
        qDebug() << "Load staff query error:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->table_staff->insertRow(row);
        for (int col = 0; col < 6; ++col) { // 6 columns in select
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->table_staff->setItem(row, col, item);
        }
        row++;
    }
    ui->totalstaff->setText("Total no. of staff: " + QString::number(row));
    ui->totalstaff->setAlignment(Qt::AlignCenter);
}


void staff::on_ADDSTAFF_clicked()
{
    addstaff *ptraddstaff = new addstaff(this);
    int result = ptraddstaff->exec(); // modal dialog
    delete ptraddstaff;

    if (result == QDialog::Accepted) {
        this->close();           // close current staff window
        staff *newStaff = new staff();  // re-create fresh staff window
        newStaff->show();        // show the refreshed window
    }
}


