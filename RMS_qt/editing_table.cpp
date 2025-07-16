#include "editing_table.h"
#include "ui_editing_table.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QRegularExpressionValidator>

editing_table::editing_table(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editing_table)
{
    ui->setupUi(this);
    QSqlDatabase &db = DatabaseManager::getDatabase();


    // Make table_no field non-editable
    ui->lineEdit_e1->setReadOnly(true);

    // Validators
    QIntValidator *intValidator = new QIntValidator(1, 9999, this);
    ui->lineEdit_e1->setValidator(intValidator);
    ui->lineEdit_e2->setValidator(intValidator);

    QRegularExpression rx("[a-zA-Z\\s]+");
    QRegularExpressionValidator *stringValidator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit_e3->setValidator(stringValidator);
    ui->lineEdit_e5->setValidator(stringValidator);
}

editing_table::~editing_table()
{
    delete ui;
}

void editing_table::setData(const QString &tableNo, const QString &seats, const QString &location,
                            const QString &type, const QString &description)
{
    original_table_no = tableNo;

    ui->lineEdit_e1->setText(tableNo);
    ui->lineEdit_e2->setText(seats);
    ui->lineEdit_e3->setText(location);
    ui->lineEdit_e5->setText(type);
    ui->textEdit_1->setPlainText(description);
}

void editing_table::on_btn_cancel_clicked()
{
    this->close();
    if (parentWidget()) parentWidget()->show();
}

void editing_table::on_btn_change_clicked()
{
    QString Seats = ui->lineEdit_e2->text();
    QString Location = ui->lineEdit_e3->text();
    QString Type = ui->lineEdit_e5->text();
    QString Description = ui->textEdit_1->toPlainText();

    if (Seats.isEmpty() || Location.isEmpty()  ||
        Type.isEmpty() || Description.isEmpty()) {
        QMessageBox::warning(this, "Missing Fields", "Please fill in all fields.");
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE table_assign SET seats=?, location=?, table_type=?, description=? "
                  "WHERE table_no=?");

    query.addBindValue(Seats);
    query.addBindValue(Location);
    query.addBindValue(Type);
    query.addBindValue(Description);
    query.addBindValue(original_table_no); // Don't change table_no

    QSqlQuery queryTables;
    queryTables.prepare("UPDATE tables set seats=?, remarks=? where table_no=?");
    queryTables.addBindValue(Seats);
    queryTables.addBindValue(Description);
    queryTables.addBindValue(original_table_no);

    if (!query.exec() || !queryTables.exec()) {
        QMessageBox::critical(this, "Error", "Failed to update: " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Updated", "Record updated successfully!");

    emit dataUpdated();
    this->close();
}

