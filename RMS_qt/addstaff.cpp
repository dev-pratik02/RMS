#include "addstaff.h"
#include "ui_addstaff.h"
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QSqlQuery>
#include <QSqlError>
#include "databasemanager.h"

addstaff::addstaff(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addstaff)
{
    ui->setupUi(this);

    QSqlDatabase &db = DatabaseManager::getDatabase();

    if (!db.open()) {
        qDebug() << "Addstaff DB open error:" << db.lastError().text();
    }

    // Set staff_id box read-only
    ui->input_id->setReadOnly(true);

    // Load next available staff_id (guessed as max + 1)
    QSqlQuery idQuery(db);
    if (idQuery.exec("SELECT IFNULL(MAX(staff_id), 0) + 1 FROM staff")) {
        if (idQuery.next()) {
            int nextId = idQuery.value(0).toInt();
            ui->input_id->setText(QString::number(nextId));
        }
    } else {
        qDebug() << "Could not fetch next ID:" << idQuery.lastError().text();
    }

    // Validators
    QRegularExpression digitOnlyRegex("^\\d*$");  // digits only
    ui->input_contact->setValidator(new QRegularExpressionValidator(digitOnlyRegex, this));
    ui->input_contact->setMaxLength(10);  // max 10 digits

    ui->input_age->setValidator(new QIntValidator(18, 99, this));
    ui->input_salary->setValidator(new QDoubleValidator(0, 1000000, 2, this));

    QRegularExpression namePositionRegex("^[a-zA-Z\\s]*$");
    ui->input_name->setValidator(new QRegularExpressionValidator(namePositionRegex, this));
    ui->input_position->setValidator(new QRegularExpressionValidator(namePositionRegex, this));
}

addstaff::~addstaff()
{
    delete ui;
}

void addstaff::on_btn_add_clicked()
{
    QString name = ui->input_name->text().trimmed();
    QString position = ui->input_position->text().trimmed();
    QString salary = ui->input_salary->text().trimmed();
    QString age = ui->input_age->text().trimmed();
    QString contact = ui->input_contact->text().trimmed();

    if (name.isEmpty() || position.isEmpty() || salary.isEmpty() || age.isEmpty() || contact.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields.");
        return;
    }

    if (contact.length() != 10) {
        QMessageBox::warning(this, "Input Error", "Contact number must be exactly 10 digits.");
        return;
    }

    QSqlDatabase &db = DatabaseManager::getDatabase();
    QSqlQuery query(db);
    query.prepare("INSERT INTO staff (staff_name, position, salary, age, contact) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(position);
    query.addBindValue(salary);
    query.addBindValue(age);
    query.addBindValue(contact);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to add staff: " + query.lastError().text());
        return;
    }

    int newId = query.lastInsertId().toInt();
    QMessageBox::information(this, "Success", "Staff added successfully!\nGenerated ID: " + QString::number(newId));

    accept(); // Close dialog and signal success
}

void addstaff::on_btn_reset_clicked()
{
    ui->input_name->clear();
    ui->input_position->clear();
    ui->input_salary->clear();
    ui->input_age->clear();
    ui->input_contact->clear();

    // Reload next ID after reset
    QSqlDatabase &db = DatabaseManager::getDatabase();
    QSqlQuery idQuery(db);
    if (idQuery.exec("SELECT IFNULL(MAX(staff_id), 0) + 1 FROM staff")) {
        if (idQuery.next()) {
            int nextId = idQuery.value(0).toInt();
            ui->input_id->setText(QString::number(nextId));
        }
    }
}
