#include "editmenuitem.h"
#include "ui_editmenuitem.h"


QByteArray image_data;

editmenuitem::editmenuitem(QString id, QString name, QString price, QString description,QString category, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::editmenuitem),
    itemId(id)
{
    ui->setupUi(this);
    ui->item_id->setText(id);
    ui->item_name->setText(name);
    ui->item_price->setText(price);
    ui->item_description->setText(description);

    QSqlQuery query;
    if (query.exec("SELECT [category_name] FROM category")) {
        while (query.next()) {
            QString categoryName = query.value(0).toString();
            ui->combo_category->addItem(categoryName);
        }
    } else {
        qDebug() << "Failed to load categories:" << query.lastError().text();
    }


    QDoubleValidator *priceValidator = new QDoubleValidator(0.0, 99999.99, 2, this);
    priceValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->item_price->setValidator(priceValidator);
    ui->item_price->setPlaceholderText("Enter valid price");
    ui->item_name->setPlaceholderText("Enter item name");
    ui->combo_category->setPlaceholderText("Enter item category");
    ui->item_description->setPlaceholderText("Enter description");

    ui->item_id->setReadOnly(true);


    QSqlQuery imageQuery;
    imageQuery.prepare("SELECT image FROM menu WHERE menu_item_id = ?");
    imageQuery.addBindValue(id);
    if (imageQuery.exec()) {
        if (imageQuery.next()) {
            image_data = imageQuery.value(0).toByteArray();
            QPixmap pixmap;
            pixmap.loadFromData(image_data);
            ui->image_preview->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
        }
    } else {
        qDebug() << "Failed to load image:" << imageQuery.lastError();
    }


}

editmenuitem::~editmenuitem()
{
    delete ui;

}
void editmenuitem::on_btn_save_clicked()
{
    QString name = ui->item_name->text();
    QString category = ui->combo_category->currentText();
    QString price = ui->item_price->text();
    QString description = ui->item_description->text();

    qDebug() << "Name:" << name;
    qDebug() << "Category:" << category;
    qDebug() << "Price:" << price;
    qDebug() << "Description:" << description;

    if (name.isEmpty() || category.isEmpty()|| price.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "Validation", "All fields must be filled.");
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE menu SET [item_name] = ?,category = ?, price = ?, description = ?, image = ? WHERE [menu_item_id] = ?");
    query.addBindValue(name);
    query.addBindValue(category);
    query.addBindValue(price);
    query.addBindValue(description);
    query.addBindValue(image_data);
    query.addBindValue(itemId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Item updated successfully.");
    emit dataUpdated();
    this->close();
}
void editmenuitem::on_btn_reset_clicked()
{
    ui->item_name->clear();
    ui->item_price->clear();
    ui->item_description->clear();
    ui->image_preview->clear();
}


void editmenuitem::on_image_upload_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.jpeg)");
    if (!imagePath.isEmpty()) {
        QPixmap pix(imagePath);
        ui->image_preview->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio));  // Optional preview
    }

    QFile file(imagePath);
    if (file.open(QIODevice::ReadOnly)) {
        image_data = file.readAll();
        file.close();
    }
}

