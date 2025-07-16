#include "addstaff.h"
#include "ui_addstaff.h"
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

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

    // Setup validators
    QRegularExpression rx("^\\d{10}$");
    ui->input_contact->setValidator(new QRegularExpressionValidator(rx, this));
    ui->input_age->setValidator(new QIntValidator(18, 99, this));
    ui->input_salary->setValidator(new QDoubleValidator(0, 1000000, 2, this));

    QRegularExpression rx2("^[a-zA-Z\\s]*$");
    ui->input_name->setValidator(new QRegularExpressionValidator(rx2, this));
    ui->input_position->setValidator(new QRegularExpressionValidator(rx2, this));
}

addstaff::~addstaff()
{
    delete ui;
}

void addstaff::on_btn_add_clicked()
{
    QString name = ui->input_name->text();
    QString position = ui->input_position->text();
    QString salary = ui->input_salary->text();
    QString age = ui->input_age->text();
    QString contact = ui->input_contact->text();

    if (name.isEmpty() || position.isEmpty() || salary.isEmpty() || age.isEmpty() || contact.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields.");
        return;
    }

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

    QMessageBox::information(this, "Success", "Staff added successfully!");
    accept(); // Close dialog and signal success
}

void addstaff::on_btn_reset_clicked()
{
    ui->input_name->clear();
    ui->input_position->clear();
    ui->input_salary->clear();
    ui->input_age->clear();
    ui->input_contact->clear();
}
