#include "menu.h"
#include "addmenuitem.h"
#include "editmenuitem.h"
#include "ui_menu.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QPushButton>

menu::menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    ptraddmenuitem = new addmenuitem();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Swift/OneDrive/Desktop/Database/menu.db");

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";
        loadData();
    }
}
menu::~menu()
{
    delete ui;
}
void menu::loadData()
{
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    QSqlQuery query("SELECT [ITEM ID], [ITEM NAME], PRICE, DESCRIPTION FROM menu");
    int row = 0;

    while (query.next()) {

            QString id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString price = query.value(2).toString();
            QString description = query.value(3).toString();

            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(id));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(name));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(price));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(description));

            QWidget *actionWidget = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(actionWidget);
            layout->setContentsMargins(0, 0, 0, 0);

            // Edit button
            QPushButton *editBtn = new QPushButton("Edit");
            connect(editBtn, &QPushButton::clicked, this, [=]() {
                handleEditButton(id, name, price, description);
            });
            layout->addWidget(editBtn);

            // Delete button
            QPushButton *deleteBtn = new QPushButton("Delete");
            connect(deleteBtn, &QPushButton::clicked, this, [=]() {
            handleDeleteButton(id);
            });
            layout->addWidget(deleteBtn);

            ui->tableWidget->setCellWidget(row, 4, actionWidget);
            row++;
    }

        qDebug() << "Loaded" << row << "rows into table.";
    }

void menu::handleEditButton(QString id, QString name, QString price, QString description)
{
    editmenuitem *editWin = new editmenuitem(id, name, price, description, this);
    connect(editWin, &editmenuitem::dataUpdated, this, [=]() {
        loadData();
    });

    editWin->exec();
}

void menu::handleDeleteButton(QString id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM menu WHERE [ITEM ID] = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Delete Failed", query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Deleted", "Item deleted successfully.");
    loadData();  // Refresh table
}


void menu::on_btn_addmenu_clicked()
{
    addmenuitem *addDialog = new addmenuitem(this);

    connect(addDialog, &addmenuitem::itemSaved, this, [=]() {
        this->close();
        menu *newMenu = new menu();
        newMenu->show();
    });

    addDialog->exec();
}
void menu::on_btn_edit_clicked()
{
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow < 0) return;

    QString id = ui->tableWidget->item(selectedRow, 0)->text();
    QString name = ui->tableWidget->item(selectedRow, 1)->text();
    QString price = ui->tableWidget->item(selectedRow, 2)->text();
    QString description = ui->tableWidget->item(selectedRow, 3)->text();

   editmenuitem *editWin = new editmenuitem(id, name, price, description, this);

    connect(editWin, &editmenuitem::dataUpdated, this, [=]() {
        loadData();
   });


    editWin->exec();
}
