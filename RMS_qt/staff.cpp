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
        //dbPath = QDir::cleanPath(dbPath
        mydb.setDatabaseName(dbPath);
    } else {
        mydb = QSqlDatabase::database("qt_sql_default_connection");
    }

    if (mydb.open()) {
        qDebug() << "Database is accessed by staff page";
    } else {
        qDebug() << "Database connection failed";
        qDebug() << "Error:" << mydb.lastError();
    }

    QSqlQuery queryStaff(mydb);
    queryStaff.prepare("SELECT staff_id, staff_name, position, age, contact FROM staff");
    if (queryStaff.exec()) {
        qDebug() << "Accessed staff info from database";

        int row = 0;
        while (queryStaff.next()) {
            ui->table_staff->insertRow(row); // Insert empty row

            for (int col = 0; col < queryStaff.record().count(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(queryStaff.value(col).toString());
                item->setTextAlignment(Qt::AlignCenter);  // Center-align the text
                ui->table_staff->setItem(row, col, item);
            }
            row++;
        }

        ui->totalstaff->setText("Total no. of staff: " + QString::number(row).trimmed());
        ui->totalstaff->setAlignment(Qt::AlignCenter);

    } else {
        qDebug() << "Could not access staff";
        qDebug() << queryStaff.lastError();
    }
}

staff::~staff()
{
    delete ui;
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


