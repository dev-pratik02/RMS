#include "add_tables.h"
#include "ui_add_tables.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QRegularExpressionValidator>
add_tables::add_tables(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_tables)
{
    ui->setupUi(this);
    db = QSqlDatabase::database();
    QIntValidator *intValidator = new QIntValidator(1, 9999, this);
    ui->lineEdit_1->setValidator(intValidator);  // Table No.
    ui->lineEdit_2->setValidator(intValidator);  // Seats

    // String-only validator for Location, Orientation, Quality
    QRegularExpression rx("[a-zA-Z\\s]+");  // Only letters and spaces
    QRegularExpressionValidator *stringValidator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit_3->setValidator(stringValidator);
    ui->lineEdit_4->setValidator(stringValidator);
    ui->lineEdit_5->setValidator(stringValidator);
}

add_tables::~add_tables()
{
    delete ui;
}

void add_tables::on_btn_save_clicked()
{
    QString Table_NO = ui->lineEdit_1->text();
    QString Seats = ui->lineEdit_2->text();
    QString Location = ui->lineEdit_3->text();
    QString Orientation = ui->lineEdit_4->text();
    QString Quality = ui->lineEdit_5->text();
    QString Description = ui->textEdit_1->toPlainText();
    QString Status = "Available";

    if (Table_NO.isEmpty() || Seats.isEmpty() || Location.isEmpty() ||
        Orientation.isEmpty() || Quality.isEmpty() || Description.isEmpty()) {
        QMessageBox::warning(this, "Missing Fields", "Please fill in all fields before saving.");
        return;
    }

    // Validate numeric inputs
    bool ok1, ok2;
    int tableNoInt = Table_NO.toInt(&ok1);
    int seatsInt = Seats.toInt(&ok2);
    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Input Error", "Table No. and Seats must be numbers.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO table_list (table_no, seats, location, orientation, quality, description, status) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(tableNoInt);
    query.addBindValue(seatsInt);
    query.addBindValue(Location);
    query.addBindValue(Orientation);
    query.addBindValue(Quality);
    query.addBindValue(Description);
    query.addBindValue(Status);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to save data: " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Saved successfully!");

    // ✅ Clear the form after saving
    on_btn_reset_clicked();

    // ✅ Emit signal to refresh edit page
    emit dataSaved();
}


void add_tables::on_btn_reset_clicked()
{
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
     ui->lineEdit_3->clear();
     ui->lineEdit_4->clear();
     ui->lineEdit_5->clear();
    ui->textEdit_1->clear();
}

void add_tables::on_btn_back1_clicked()
{
    this->hide();
    if (parentWidget()) {
        parentWidget()->show();
    }
}
