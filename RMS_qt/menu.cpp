#include "menu.h"
#include "ui_menu.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>

menu::menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    ptraddmenuitem = new addmenuitem();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Swift/OneDrive/Desktop/Database/menu.db");  // Ensure this file exists in the .exe folder

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";
    }


    QSqlQuery query(db);
    query.prepare("SELECT * FROM menu");

    if(query.exec()){
        int row = 0;
        while (query.next()) {
            ui->tableWidget->insertRow(row);

            QString id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString price = query.value(2).toString();
            QString description = query.value(3).toString();

            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(id));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(name));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(price));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(description));

            QPushButton *editBtn = new QPushButton("Edit");
            ui->tableWidget->setCellWidget(row, 4, editBtn);

            // Store button index using a lambda
            connect(editBtn, &QPushButton::clicked, this, [=]() {
                handleEditButton(id, name, price,description);
            });

            row++;
        }


        qDebug() << "Loaded" << row << "rows into table.";
    }
    else{
        qDebug() << "could not execute the commands";
        qDebug()<< query.lastError();
    }
}

void menu::handleEditButton(QString id, QString name, QString price,QString description)
{
    editmenuitem *editWin = new editmenuitem(id, name, price,description, this);
    editWin->setAttribute(Qt::WA_DeleteOnClose); // Auto-delete on close
    editWin->show();
}

menu::~menu()
{
    delete ui;
}

void menu::on_btn_addmenu_clicked()
{
    ptraddmenuitem->show();
}



