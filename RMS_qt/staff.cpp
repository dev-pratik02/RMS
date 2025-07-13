// staff.cpp
#include "staff.h"
#include "ui_staff.h"
#include "editstaff.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>

staff::staff(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::staff)
{
    ui->setupUi(this);

    qDebug() << "The application dir path is:\n" << QCoreApplication::applicationDirPath();

    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Users/VICTUS/OneDrive/Desktop/sanat/RMS_qt/RmsApp.db");
        // mydb.setDatabaseName("/Users/pratik/Programming/RMS/RMS_qt/RmsApp.db");
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
    ui->table_staff->setColumnCount(7); // 6 data columns + 1 action column
    QStringList headers = {"ID", "Name", "Position", "Salary", "Age", "Contact", "Action"};
    ui->table_staff->setHorizontalHeaderLabels(headers);

    ui->table_staff->setRowCount(0); // Clear existing rows

    QSqlQuery query(mydb);
    if (!query.exec("SELECT staff_id, staff_name, position, salary, age, contact FROM staff")) {
        qDebug() << "Load staff query error:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->table_staff->insertRow(row);

        for (int col = 0; col < 6; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->table_staff->setItem(row, col, item);
        }

        QPushButton *editBtn = new QPushButton("Edit");
        QPushButton *deleteBtn = new QPushButton("Delete");

        editBtn->setStyleSheet("background-color: lightblue;");
        deleteBtn->setStyleSheet("background-color: lightcoral;");

        QWidget *actionWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionWidget);
        layout->addWidget(editBtn);
        layout->addWidget(deleteBtn);
        layout->setContentsMargins(5, 0, 5, 0);
        actionWidget->setLayout(layout);

        ui->table_staff->setCellWidget(row, 6, actionWidget);

        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString position = query.value(2).toString();
        QString salary = query.value(3).toString();
        QString age = query.value(4).toString();
        QString contact = query.value(5).toString();

        connect(editBtn, &QPushButton::clicked, this, [=]() {
            editstaff *editDialog = new editstaff(this);
            editDialog->setData(id, name, position, salary, age, contact);

            if (editDialog->exec() == QDialog::Accepted) {
                QSqlQuery updateQuery;
                updateQuery.prepare("UPDATE staff SET staff_name = ?, position = ?, salary = ?, age = ?, contact = ? WHERE staff_id = ?");
                updateQuery.addBindValue(editDialog->getName());
                updateQuery.addBindValue(editDialog->getPosition());
                updateQuery.addBindValue(editDialog->getSalary());
                updateQuery.addBindValue(editDialog->getAge());
                updateQuery.addBindValue(editDialog->getContact());
                updateQuery.addBindValue(id);

                if (!updateQuery.exec()) {
                    qDebug() << "Update failed:" << updateQuery.lastError().text();
                } else {
                    loadStaffData();
                }
            }

            delete editDialog;
        });

        connect(deleteBtn, &QPushButton::clicked, this, [=]() {
            QSqlQuery deleteQuery;
            deleteQuery.prepare("DELETE FROM staff WHERE staff_id = ?");
            deleteQuery.addBindValue(id);

            if (!deleteQuery.exec()) {
                qDebug() << "Delete failed:" << deleteQuery.lastError().text();
            } else {
                loadStaffData();
            }
        });

        row++;
    }

    ui->totalstaff->setText("Total no. of staff: " + QString::number(row));
    ui->totalstaff->setAlignment(Qt::AlignCenter);

    // ui->table_staff->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void staff::on_ADDSTAFF_clicked()
{
    addstaff *ptraddstaff = new addstaff(this);
    int result = ptraddstaff->exec();
    delete ptraddstaff;

    if (result == QDialog::Accepted) {
        loadStaffData(); // Refresh table instead of re-opening window
    }
}
