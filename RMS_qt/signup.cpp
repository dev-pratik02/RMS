#include "signup.h"
#include "utils.h"
#include "ui_signup.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QLineEdit>
#include <QDebug>
#include <QToolButton>
#include <QIcon>
#include <QStyle>
#include <QCryptographicHash>
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include <QEvent>
#include "databasemanager.h"

signup::signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signup)
{
    ui->setupUi(this);
    ui->line_password->setEchoMode(QLineEdit::Password);
    ui->line_confirmpass->setEchoMode(QLineEdit::Password);

    ui->line_phone->setValidator(new QIntValidator(0, 9999999999, this));

    QRegularExpression nameRegex("^[A-Za-z ]+$");
    QValidator *nameValidator = new QRegularExpressionValidator(nameRegex, this);
    ui->line_name->setValidator(nameValidator);

    QDate maxDate = QDate::currentDate().addYears(-18);
    ui->date_dob->setMaximumDate(maxDate);

    setupEyeButton(ui->line_password);
    setupEyeButton(ui->line_confirmpass);

    qDebug() << "line_password valid:" << ui->line_password;
    qDebug() << "line_confirmpass valid:" << ui->line_confirmpass;

}


signup::~signup()
{
    delete ui;
}

bool signup::openDatabase()
{
    QSqlDatabase &db = DatabaseManager::getDatabase();


    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError();
        return false;
    }
    return true;
}

void signup::on_btn_confirm_clicked()
{
    QString name = ui->line_name->text().trimmed();
    QString phone = ui->line_phone->text().trimmed();
    QString email = ui->line_email->text().trimmed();
    QString dob = ui->date_dob->date().toString("yyyy-MM-dd");
    QString pass = ui->line_password->text();
    QString confirmpass = ui->line_confirmpass->text();
    QString username = ui->input_username->text();
    if (name.isEmpty() || username.isEmpty()|| phone.isEmpty() || email.isEmpty() || pass.isEmpty() || confirmpass.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all the fields.");
        return;
    }

    if (pass != confirmpass) {
        QMessageBox::warning(this, "Password Error", "Passwords do not match.");
        return;
    }
    if (!isValidEmail(email)) {
        QMessageBox::warning(this, "Email Error", "Please enter a valid email address.");
        return;
    }


    // Connect to DB
    if (!openDatabase())
        return;

    QString hashedPass = hashPassword(pass);
    QSqlQuery query;
    query.prepare("INSERT INTO users (name, phone, email, dob, password, username) "
                  "VALUES (?, ?, ?, ?, ?,?)");
    query.addBindValue(name);
    query.addBindValue(phone);
    query.addBindValue(email);
    query.addBindValue(dob);
    query.addBindValue(hashedPass);
    query.addBindValue(username);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Signup successful!");
        this->close();
    }

    QSqlDatabase::database().close();
}


