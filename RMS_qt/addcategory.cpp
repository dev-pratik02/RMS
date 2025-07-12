#include "addcategory.h"
#include "ui_addcategory.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QIntValidator>

addcategory::addcategory(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addcategory)
{
    ui->setupUi(this);
    // Validator for category_id (only integers)
    QIntValidator* idValidator = new QIntValidator(1, 9999, this);  // Adjust range as needed
    ui->category_id->setValidator(idValidator);

    // Validator for item_no (only integers)
    QIntValidator* itemNoValidator = new QIntValidator(1, 999, this);  // Adjust range as needed
    ui->item_no->setValidator(itemNoValidator);
}

addcategory::~addcategory()
{
    delete ui;
}

void addcategory::on_btn_add_clicked()
{
    QString name = ui->category_name->text().trimmed();
    QString id = ui->category_id->text().trimmed();
    QString num = ui->item_no->text().trimmed();
    QString desc = ui->category_description->toPlainText().trimmed();

    if (name.isEmpty() || id.isEmpty() || num.isEmpty() || desc.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO category ([category_name], [category_id], [display_order], [description]) "
                  "VALUES (:name, :id, :num, :desc)");
    query.bindValue(":name", name);
    query.bindValue(":id", id);
    query.bindValue(":num", num);
    query.bindValue(":desc", desc);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Category added successfully!");
    accept();
    emit categoryUpdated();

}

void addcategory::setValues(QString name, QString id, QString itemCount, QString description)
{
    ui->category_name->setText(name);
    ui->category_id->setText(id);
    ui->item_no->setText(itemCount);
    ui->category_description->setPlainText(description);
}

