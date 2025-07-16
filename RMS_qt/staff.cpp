#include "staff.h"
#include "ui_staff.h"
#include "editstaff.h"
#include "addstaff.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QHeaderView>

staff::staff(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::staff)
{
    ui->setupUi(this);

    qDebug() << "The application dir path is:\n" << QCoreApplication::applicationDirPath();

    QSqlDatabase &db = DatabaseManager::getDatabase();


    if (db.open()) {
        qDebug() << "Database is accessed by staff page";
    } else {
        qDebug() << "Database connection failed";
        qDebug() << "Error:" << db.lastError();
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

    // Set font for "Action" header column (index 6)
    QFont headerFont("Arial", 12, QFont::Normal);
    QTableWidgetItem *actionHeaderItem = ui->table_staff->horizontalHeaderItem(6);
    if (actionHeaderItem) {
        actionHeaderItem->setFont(headerFont);
    }

    ui->table_staff->setRowCount(0); // Clear existing rows

    QSqlQuery query(db);
    if (!query.exec("SELECT staff_id, staff_name, position, salary, age, contact FROM staff")) {
        qDebug() << "Load staff query error:" << query.lastError().text();
        return;
    }

    QColor columnColors[6] = {
        QColor("#FFF2CC"), // ID - light yellow
        QColor("#D9EAD3"), // Name - light green
        QColor("#CFE2F3"), // Position - light blue
        QColor("#F4CCCC"), // Salary - light red
        QColor("#EAD1DC"), // Age - light pink
        QColor("#D9D2E9")  // Contact - light purple
    };

    int row = 0;
    while (query.next()) {
        ui->table_staff->insertRow(row);

        // Add colored items
        for (int col = 0; col < 6; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setTextAlignment(Qt::AlignCenter);
            item->setBackground(columnColors[col]);
            ui->table_staff->setItem(row, col, item);
        }

        // Create action buttons
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

    // Stretch columns to fit window
    ui->table_staff->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
