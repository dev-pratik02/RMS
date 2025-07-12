#include "addmenuitem.h"
#include "ui_addmenuitem.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>

addmenuitem::addmenuitem(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addmenuitem)
{
    ui->setupUi(this);

    ui->item_id->setPlaceholderText("Enter Item ID");
    ui->item_name->setPlaceholderText("Enter Item Name");
    ui->item_price->setPlaceholderText("Enter Price");
    ui->item_description->setPlaceholderText("Enter Description");
}

addmenuitem::~addmenuitem()
{
    delete ui;
}
void addmenuitem::on_btn_save_clicked()
{
    QString itemid = ui->item_id->text();
    QString name = ui->item_name->text();
    QString price = ui->item_price->text();
    QString description = ui->item_description->toPlainText();

    if (itemid.isEmpty() || name.isEmpty() || price.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all required fields.");
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Swift/OneDrive/Desktop/Database/menu.db");

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";
    }

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
        qDebug() << "Database connection failed:" << db.lastError().text();
        return;
    } else {
        qDebug() << "Database connected successfully!";
    }

    QSqlQuery query;
    query.prepare("INSERT INTO menu ([ITEM ID],[ITEM NAME],[PRICE],[DESCRIPTION]) "
                  "VALUES (:itemid, :name, :price, :description)");
    query.bindValue(":itemid", itemid);
    query.bindValue(":name", name);
    query.bindValue(":price", price);
    query.bindValue(":description", description);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        qDebug() << "Insert error:" << query.lastError().text();
    } else {
        QMessageBox::information(this, "Success", "Menu item added successfully!");

        ui->item_id->clear();
        ui->item_name->clear();
        ui->item_price->clear();
        ui->item_description->clear();
    }
    emit itemSaved();
    this->accept();
}
