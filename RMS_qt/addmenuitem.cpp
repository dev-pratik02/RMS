#include "addmenuitem.h"
#include "ui_addmenuitem.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QIntValidator>
#include <QDoubleValidator>

addmenuitem::addmenuitem(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addmenuitem)
{
    ui->setupUi(this);

    ui->item_id->setPlaceholderText("Generated Automatically");
    ui->item_name->setPlaceholderText("Enter Item Name");
    ui->item_category->setPlaceholderText("Enter Item Category");
    ui->item_price->setPlaceholderText("Enter Price");
    ui->item_description->setPlaceholderText("Enter Description");
    ui->item_id->setReadOnly(true);


    // Validator for item_id (only integers)
    QIntValidator *idValidator = new QIntValidator(1, 9999, this); // Adjust range if needed
    ui->item_id->setValidator(idValidator);

    // Validator for item_price (only decimal numbers with 2 digits after decimal point)
    QDoubleValidator *priceValidator = new QDoubleValidator(0.0, 99999.99, 2, this);
    priceValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->item_price->setValidator(priceValidator);

}

addmenuitem::~addmenuitem()
{
    delete ui;
}
void addmenuitem::on_btn_save_clicked()
{
    QString name = ui->item_name->text();
    QString category = ui->item_category->text();
    QString price = ui->item_price->text();
    QString description = ui->item_description->toPlainText();

    if ( name.isEmpty() ||category.isEmpty() || price.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all required fields.");
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Swift/RMS/RMS_qt/RmsApp.db");

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";
    }


    QSqlQuery query;
    query.prepare("INSERT INTO menu ([menu_item_id],[item_name], [category] ,[price],[description]) "
                  "VALUES (:itemid, :name, :category, :price, :description)");
    query.bindValue(":name", name);
    query.bindValue(":category", category);
    query.bindValue(":price", price);
    query.bindValue(":description", description);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        qDebug() << "Insert error:" << query.lastError().text();
    } else {
        QMessageBox::information(this, "Success", "Menu item added successfully!");

        ui->item_category->clear();
        ui->item_name->clear();
        ui->item_price->clear();
        ui->item_description->clear();
    }
    emit itemSaved();
    this->accept();
}
void addmenuitem::on_btn_reset_clicked()
{
    ui->item_category->clear();
    ui->item_name->clear();
    ui->item_price->clear();
    ui->item_description->clear();
}
