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


    // Validator for item_no (only integers)
    QIntValidator* itemNoValidator = new QIntValidator(1, 99, this);  // Adjust range as needed
    ui->item_no->setValidator(itemNoValidator);

    ui->category_name->setPlaceholderText("Enter Category Name");
    ui->item_no->setPlaceholderText("Enter the display order");
    ui->category_description->setPlaceholderText("Enter Description");
}

addcategory::~addcategory()
{
    delete ui;
}

void addcategory::on_btn_add_clicked()
{
    QString name = ui->category_name->text().trimmed();
    QString num = ui->item_no->text().trimmed();
    QString desc = ui->category_description->toPlainText().trimmed();

    if (name.isEmpty()|| num.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO category ([category_name], [display_order], [description]) "
                  "VALUES (:name,:num, :desc)");
    query.bindValue(":name", name);
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

void addcategory::on_btn_reset_clicked()
{
    ui->category_name->clear();
    ui->item_no->clear();
    ui->category_description->clear();
}

void addcategory::setValues(QString name, QString itemCount, QString description)
{
    ui->category_name->setText(name);
    ui->item_no->setText(itemCount);
    ui->category_description->setPlainText(description);
}

