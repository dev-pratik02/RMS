#include "add_tables.h"
#include "ui_add_tables.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QRegularExpressionValidator>
#include "databasemanager.h"

add_tables::add_tables(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_tables)
{
    ui->setupUi(this);

    QIntValidator *intValidator = new QIntValidator(1, 9999, this);
    ui->lineEdit_2->setValidator(intValidator);  // Seats

    QRegularExpression rx("[a-zA-Z\\s]+");
    QRegularExpressionValidator *stringValidator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit_3->setValidator(stringValidator);
    ui->lineEdit_5->setValidator(stringValidator);
    ui->lineEdit_2->setPlaceholderText("Enter Seats (numbers only)");
    ui->lineEdit_3->setPlaceholderText("Enter Location");
    ui->lineEdit_5->setPlaceholderText("Enter table type");
    ui->textEdit_1->setPlaceholderText("#Description");
}

add_tables::~add_tables()
{
    delete ui;
}


void add_tables::on_btn_save_clicked()
{
    QString Seats = ui->lineEdit_2->text();
    QString Location = ui->lineEdit_3->text();
    QString Type = ui->lineEdit_5->text();
    QString Description = ui->textEdit_1->toPlainText();

    if (Type.isEmpty() || Seats.isEmpty() || Location.isEmpty() || Description.isEmpty()) {
        QMessageBox::warning(this, "Missing Fields", "Please fill in all fields before saving.");
        return;
    }

    // Validate numeric inputs
    bool ok1;
    int seatsInt = Seats.toInt(&ok1);
    if (!ok1) {
        QMessageBox::warning(this, "Input Error", "Seats must be numbers.");
        return;
    }

    QSqlDatabase &db = DatabaseManager::getDatabase();
    QSqlQuery query(db);
    query.prepare("INSERT INTO table_assign (seats, location, table_type, description) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(seatsInt);
    query.addBindValue(Location);
    query.addBindValue(Type);
    query.addBindValue(Description);

    QSqlQuery queryTables(db);
    queryTables.prepare("INSERT INTO tables(seats, status, order_id,remarks) VALUES(?,'available','',?)");
    queryTables.addBindValue(seatsInt);
    queryTables.addBindValue(Description);

    if (!query.exec() || !queryTables.exec()) {
        QMessageBox::critical(this, "Error", "Failed to save data: " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Saved successfully!");


    on_btn_reset_clicked();

    emit dataSaved();
     // setNextTableNumber();
}


void add_tables::on_btn_reset_clicked()
{
    ui->lineEdit_2->clear();
     ui->lineEdit_3->clear();
     ui->lineEdit_5->clear();
    ui->textEdit_1->clear();
      // setNextTableNumber();
}

void add_tables::on_btn_back1_clicked()
{
    this->hide();
    if (parentWidget()) {
        parentWidget()->show();
    }

}
