#include "editcategory.h"
#include "ui_editcategory.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

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

    if (newName.isEmpty() || newId.isEmpty() || newItem.isEmpty() || newDesc.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE category SET [category name]=:name, [category id]=:id, [no of items]=:num, [description]=:desc WHERE [category id]=:originalId");
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
