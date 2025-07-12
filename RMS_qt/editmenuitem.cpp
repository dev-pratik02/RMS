#include "editmenuitem.h"
#include "ui_editmenuitem.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QMessageBox>

editmenuitem::editmenuitem(QString id, QString name, QString price, QString description, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::editmenuitem),
    itemId(id)
{
    ui->setupUi(this);
    ui->item_id->setText(id);
    ui->item_name->setText(name);
    ui->item_price->setText(price);
    ui->item_description->setText(description);
    // Validator for price (e.g., up to 99999.99 with 2 decimal points)
    QDoubleValidator *priceValidator = new QDoubleValidator(0.0, 99999.99, 2, this);
    priceValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->item_price->setValidator(priceValidator);
    ui->item_price->setPlaceholderText("Enter valid price");
    ui->item_name->setPlaceholderText("Enter item name");
    ui->item_description->setPlaceholderText("Enter description");

}

editmenuitem::~editmenuitem()
{
    delete ui;

}
void editmenuitem::on_btn_save_clicked()
{
    QString name = ui->item_name->text();
    QString price = ui->item_price->text();
    QString description = ui->item_description->text();

    qDebug() << "Name:" << name;
    qDebug() << "Price:" << price;
    qDebug() << "Description:" << description;

    if (name.isEmpty() || price.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "Validation", "All fields must be filled.");
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE menu SET [item_name] = ?, price = ?, description = ? WHERE [menu_item_id] = ?");
    query.addBindValue(name);
    query.addBindValue(price);
    query.addBindValue(description);
    query.addBindValue(itemId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Item updated successfully.");
    emit dataUpdated();
    this->close();
}
