#include "addstaff.h"
#include "ui_addstaff.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>




addstaff::addstaff(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addstaff)
{
    ui->setupUi(this);
    // Validators
    ui->input_age->setValidator(new QIntValidator(0, 99, this));
    ui->input_salary->setValidator(new QDoubleValidator(0.0, 999999.99, 2, this));
    ui->input_contact->setValidator(new QIntValidator(1000000000, 9999999999, this));

    // Regular expression to accept only letters and spaces
    QRegularExpression rx("^[a-zA-Z ]*$");

    // Validator
    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(rx, this);

    // Apply to inputs
    ui->input_name->setValidator(nameValidator);
    ui->input_position->setValidator(nameValidator);

    // Clear fields every time it's created
    ui->input_name->clear();
    ui->input_position->clear();
    ui->input_salary->clear();
    ui->input_age->clear();
    ui->input_contact->clear();
    ui->input_id->clear();


}

addstaff::~addstaff()
{
    delete ui;
}






void addstaff::on_btn_add_clicked()
{
    qDebug() << "The application dir path is :\n" << QCoreApplication::applicationDirPath();

    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        QString dbPath = QCoreApplication::applicationDirPath() + "/../../../../../../RmsApp.db";
        dbPath = QDir::cleanPath(dbPath);
        mydb.setDatabaseName(dbPath);
    } else {
        mydb = QSqlDatabase::database("qt_sql_default_connection");
    }

    if(mydb.open()){
        qDebug() <<"Database is accessed by addstaff page";
    }
    else{
        qDebug() << "Database connection failed" ;
        qDebug() << "Error:"<< mydb.lastError();
    }


    QSqlQuery queryAddStaff(mydb);
    QString name= ui->input_name->text();
    QString position= ui->input_position->text();
    QString salary= ui->input_salary->text();
    QString citizenship_no= ui->input_id->text();
    QString contact = ui->input_contact->text();
    QString age= ui->input_age->text();

    // Check for empty fields
    if (name.isEmpty() || position.isEmpty() || salary.isEmpty() ||
        citizenship_no.isEmpty() || contact.isEmpty() || age.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Please fill in all the fields before adding staff.");
        return; // stop further execution
    }

    queryAddStaff.prepare("INSERT INTO staff (staff_name, position, salary, citizenship_no, contact, age) "
                          "VALUES (?, ?, ?, ?, ?, ?)");
    queryAddStaff.addBindValue(name);
    queryAddStaff.addBindValue(position);
    queryAddStaff.addBindValue(salary);
    queryAddStaff.addBindValue(citizenship_no);
    queryAddStaff.addBindValue(contact);
    queryAddStaff.addBindValue(age);


    if (queryAddStaff.exec()) {
        qDebug() << "added staff info into database";
    }

    else {
        qDebug() << "Could not access staff";
        qDebug() << queryAddStaff.lastError();
    }

    addstaff::on_btn_reset_clicked();
    this->accept();

}


void addstaff::on_btn_reset_clicked()
{
    ui->input_id->setText("");
    ui->input_name->setText("");
    ui->input_salary->setText("");
    ui->input_position->setText("");
    ui->input_age->setText("");
    ui->input_contact->setText("");
}

