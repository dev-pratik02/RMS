#include "forgotpass.h"
#include "ui_forgotpass.h"
#include "utils.h"  // for hashPassword()
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

forgotpass::forgotpass(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::forgotpass)
{
    ui->setupUi(this);

    // Hide password inputs
    ui->line_newpass->setEchoMode(QLineEdit::Password);
    ui->line_confirmpass->setEchoMode(QLineEdit::Password);
}

forgotpass::~forgotpass()
{
    delete ui;
}

void forgotpass::on_btn_confirm_clicked()
{
    QString email = ui->line_email->text().trimmed();
    QString phone = ui->line_phone->text().trimmed();
    QString dob = ui->date_dob->date().toString("yyyy-MM-dd");
    QString newpass = ui->line_newpass->text();
    QString confirmpass = ui->line_confirmpass->text();

    if (email.isEmpty() || phone.isEmpty() || newpass.isEmpty() || confirmpass.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all the fields.");
        return;
    }

    if (newpass != confirmpass) {
        QMessageBox::warning(this, "Password Error", "Passwords do not match.");
        return;
    }

    // Open DB (use shared/named connection to avoid "database locked")
    QSqlDatabase db;
    if (QSqlDatabase::contains("my_connection")) {
        db = QSqlDatabase::database("my_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", "my_connection");
        db.setDatabaseName("C:/Users/Swift/RMS/RMS_qt/RmsApp.db");
        if (!db.open()) {
            QMessageBox::critical(this, "Database Error", db.lastError().text());
            return;
        }
    }

    // Check if record exists
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT COUNT(*) FROM users WHERE email = ? AND phone = ? AND dob = ?");
    checkQuery.addBindValue(email);
    checkQuery.addBindValue(phone);
    checkQuery.addBindValue(dob);

    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::critical(this, "Error", "Failed to verify account.");
        return;
    }

    int count = checkQuery.value(0).toInt();
    if (count != 1) {
        QMessageBox::warning(this, "Not Found", "No matching account found.");
        return;
    }

    // Update password
    QString hashed = hashPassword(newpass);
    QSqlQuery updateQuery(db);
    updateQuery.prepare("UPDATE users SET password = ? WHERE email = ?");
    updateQuery.addBindValue(hashed);
    updateQuery.addBindValue(email);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "Update Error", updateQuery.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Password reset successfully.");
        this->close();
    }

    db.close();
}
