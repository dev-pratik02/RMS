#include "addmenuitem.h"
#include "ui_addmenuitem.h"
#include "databasemanager.h"
QByteArray imageData;
addmenuitem::addmenuitem(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addmenuitem)
{
    ui->setupUi(this);
    QSqlQuery query;
    if (query.exec("SELECT [category_name] FROM category")) {
        while (query.next()) {
            QString categoryName = query.value(0).toString();
            ui->combo_category->addItem(categoryName);
        }
    } else {
        qDebug() << "Failed to load categories:" << query.lastError().text();
    }


    ui->item_name->setPlaceholderText("Enter Item Name");

    ui->item_price->setPlaceholderText("Enter Price");
    ui->item_description->setPlaceholderText("Enter Description");


    // Validator for item_price (only decimal numbers with 2 digits after decimal point)
    QDoubleValidator *priceValidator = new QDoubleValidator(0.0, 9999.99, 2, this);
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
   QString category = ui->combo_category->currentText();
    QString price = ui->item_price->text();
    QString description = ui->item_description->toPlainText();

    if ( name.isEmpty() ||category.isEmpty() || price.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all required fields.");
        return;
    }

    QSqlDatabase &db = DatabaseManager::getDatabase();



    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";
    }


    QSqlQuery query;
    query.prepare("INSERT INTO menu ([menu_item_id],[item_name], [category] ,[price],[description],[image]) "
                  "VALUES (:itemid, :name, :category, :price, :description, :image)");
    query.bindValue(":name", name);
    query.bindValue(":category", category);
    query.bindValue(":price", price);
    query.bindValue(":description", description);
    query.bindValue(":image", imageData);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        qDebug() << "Insert error:" << query.lastError().text();
    } else {
        QMessageBox::information(this, "Success", "Menu item added successfully!");

        ui->combo_category->clear();
        ui->item_name->clear();
        ui->item_price->clear();
        ui->item_description->clear();
        ui->image_preview->clear();
    }
    emit itemSaved();
    this->accept();
}
void addmenuitem::on_btn_reset_clicked()
{
    ui->item_name->clear();
    ui->item_price->clear();
    ui->item_description->clear();
    ui->image_preview->clear();

}

void addmenuitem::on_image_upload_clicked()
{

    //Image
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.jpeg *.webp)");
    if (!imagePath.isEmpty()) {
        QPixmap pix(imagePath);
        ui->image_preview->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio));  // Optional preview
    }

    QFile file(imagePath);
    if (file.open(QIODevice::ReadOnly)) {
        imageData = file.readAll();
        file.close();
    }
}

