#include "editcategory.h"
#include "ui_editcategory.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>

editcategory::editcategory(QString name, QString id, QString itemCount, QString description, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editcategory),
    originalId(id)
{
    ui->setupUi(this);

    ui->category_name->setText(name);
    ui->category_id->setText(id);
    ui->item_no->setText(itemCount);
    ui->category_description->setPlainText(description);

    ui->category_id->setReadOnly(true);

    QSqlDatabase &db = DatabaseManager::getDatabase();

     // Validator for category_id (integers only)
     QIntValidator *idValidator = new QIntValidator(1, 9999, this); // Customize range as needed
     ui->category_id->setValidator(idValidator);

     // Validator for item_no (display_order)
     QIntValidator *itemNoValidator = new QIntValidator(1, 999, this); // Customize range as needed
     ui->item_no->setValidator(itemNoValidator);
}
editcategory::~editcategory()
{
    delete ui;
}

void editcategory::on_btn_edit_clicked()
{
    QString newName = ui->category_name->text().trimmed();
    QString newId = ui->category_id->text().trimmed();
    QString newItem = ui->item_no->text().trimmed();
    QString newDesc = ui->category_description->toPlainText().trimmed();

    if (newName.isEmpty() || newId.isEmpty() || newItem.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE category SET [category_name]=:name, [category_id]=:id, [display_order]=:num, [description]=:desc WHERE [category_id]=:originalId");
    query.bindValue(":name", newName);
    query.bindValue(":id", newId);
    query.bindValue(":num", newItem);
    query.bindValue(":desc", newDesc);
    query.bindValue(":originalId", originalId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Updated", "Category updated successfully.");
    emit categoryUpdated();
    accept();
}
void editcategory::on_btn_reset_clicked()
{
    ui->category_name->clear();
    ui->item_no->clear();
    ui->category_description->clear();
}
