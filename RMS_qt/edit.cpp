#include "edit.h"
#include<table.h>
#include "ui_edit.h"
#include "databasemanager.h"
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include "editing_table.h"
edit::edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit),
    addPage(nullptr)
{
    ui->setupUi(this);

    QSqlDatabase &db = DatabaseManager::getDatabase();


    if (!db.isOpen()) {
        qDebug() << "Database not open in edit!";
    }

    loadTableView();

    connect(ui->btn_back, &QPushButton::clicked, this, &edit::on_btn_back_clicked);
    connect(ui->btn_add, &QPushButton::clicked, this, &edit::on_btn_add_clicked);
}

edit::~edit()
{
    delete ui;
}

void edit::loadTableView()
{
    QSqlQuery query(db);
    query.prepare("SELECT table_no, seats, location, table_type, description FROM table_assign");
    query.exec();
    if (query.lastError().isValid()) {
        qDebug() << "Query error:" << query.lastError().text();
        return;
    }

    // Clear existing contents and set up columns (6 data + 1 action)
    ui->table_view->clear();
    ui->table_view->setColumnCount(6);
    ui->table_view->setRowCount(0);
    QStringList headers = {"Table No", "Seats", "Location", "Table Type", "Description", "Actions"};
    ui->table_view->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        ui->table_view->insertRow(row);

        // Insert data columns
        for (int col = 0; col < 5; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->table_view->setItem(row, col, item);
        }

        // Create a QWidget with Edit and Delete buttons
        QWidget *actionWidget = new QWidget();
        QPushButton *editBtn = new QPushButton("Edit");
        QPushButton *delBtn = new QPushButton("Delete");
        QHBoxLayout *layout = new QHBoxLayout(actionWidget);
        layout->addWidget(editBtn);
        layout->addWidget(delBtn);
        layout->setContentsMargins(0, 0, 0, 0);
        actionWidget->setLayout(layout);
        ui->table_view->setCellWidget(row, 5, actionWidget);

        // Store row number in button properties for reference
        editBtn->setProperty("row", row);
        delBtn->setProperty("row", row);

        // Connect Edit button signal
        connect(editBtn, &QPushButton::clicked, this, [=]() {
            int r = editBtn->property("row").toInt();

            int tableNo = ui->table_view->item(r, 0)->text().toInt();
            QString seats = ui->table_view->item(r, 1)->text();
            QString type = ui->table_view->item(r, 2)->text();
            QString location = ui->table_view->item(r, 3)->text();
            QString description = ui->table_view->item(r, 4)->text();

            editing_table *editForm = new editing_table(this);
            editForm->setData(QString::number(tableNo), seats, type, location, description);
            connect(editForm, &editing_table::dataUpdated, this, &edit::refreshTableView);
            editForm->show();
        });

        // Connect Delete button signal
        connect(delBtn, &QPushButton::clicked, this, [=]() {
            int r = delBtn->property("row").toInt();
            QString tableNo = ui->table_view->item(r, 0)->text();

            QMessageBox::StandardButton reply = QMessageBox::question(
                this,
                "Delete Table",
                "Are you sure you want to delete Table No: " + tableNo + "?",
                QMessageBox::Yes | QMessageBox::No
                );

            if (reply == QMessageBox::Yes) {
                QSqlQuery delQuery;
                delQuery.prepare("DELETE FROM table_assign WHERE table_no = ?");
                delQuery.addBindValue(tableNo.toInt());

                QSqlQuery queryTables;
                queryTables.prepare("DELETE FROM tables WHERE table_no = ?");
                queryTables.addBindValue(tableNo.toInt());

                if (!delQuery.exec() || !queryTables.exec()) {
                    QMessageBox::critical(this, "Delete Error", "Database error: " + delQuery.lastError().text());
                } else {
                    QMessageBox::information(this, "Deleted", "Deleted successfully.");
                    refreshTableView();
                }
            }
        });

        row++;
    }

    ui->table_view->resizeColumnsToContents();
    ui->table_view->setColumnWidth(0, 80);
    ui->table_view->setColumnWidth(1, 60);
    ui->table_view->setColumnWidth(2, 100);
    ui->table_view->setColumnWidth(4, 100);
    ui->table_view->setColumnWidth(5, 150);
    ui->table_view->setColumnWidth(6, 150);
}


void edit::on_btn_back_clicked()
{
    this->hide();
    if (parentWidget()) {
        parentWidget()->show();
    }
}

void edit::on_btn_add_clicked()
{
    if (!addPage) {
        addPage = new add_tables(this);
    }
    // addPage->setNextTableNumber();
    addPage->show();
    this->hide();


    connect(addPage, &add_tables::dataSaved, this, &edit::refreshTableView);

}

void edit::on_edit_button_clicked(int row)
{
    QAbstractItemModel *model = ui->table_view->model();
    if (!model) return;


    QString table_no = model->index(row, 0).data().toString();
    QString seats = model->index(row, 1).data().toString();
    QString type = model->index(row, 2).data().toString();
    QString location = model->index(row, 3).data().toString();
    QString description = model->index(row, 4).data().toString();

    editForm = new editing_table(this);
    editForm->setData(table_no, seats, type, location, description);
    editForm->show();

    connect(editForm, &editing_table::dataUpdated, this, &edit::refreshTableView);

}


void edit::on_delete_button_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int row = button->property("row").toInt();
    QString tableNo = ui->table_view->item(row, 0)->text();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Delete Table",
        "Are you sure you want to delete Table No: " + tableNo + "?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        QSqlQuery query(db);
        query.prepare("DELETE FROM table_assign WHERE table_no = ?");
        query.addBindValue(tableNo);

        QSqlQuery queryTables(db);
        queryTables.prepare("DELETE FROM tables WHERE table_no = ?");
        queryTables.addBindValue(tableNo);

        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to update table_assign: " + query.lastError().text());
            return;
        }
        if (!queryTables.exec()) {
            QMessageBox::critical(this, "Error", "Failed to update tables: " + queryTables.lastError().text());
            return;
        }
        else {
            QMessageBox::information(this, "Deleted", "Deleted successfully.");
            query.finish();
            refreshTableView();
        }
    }
}

void edit::refreshTableView()
{
    loadTableView();
    this->show();


    table *mainWindow = qobject_cast< table *>(parentWidget());
    if (mainWindow) {
        mainWindow->refreshTableList();
    }
}

