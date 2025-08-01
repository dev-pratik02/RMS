#include "profile.h"
#include "ui_profile.h"

profile::profile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::profile)
{
    ui->setupUi(this);


    QSqlDatabase &db = DatabaseManager::getDatabase();

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";
    }

}

profile::~profile()
{
    delete ui;
}

void profile::on_logout_btn_clicked()
{

}


void profile::on_pass_btn_clicked()
{

}


void profile::on_btn_reset_clicked()
{

}


void profile::on_btn_save_clicked()
{
    QString gender = ui->maleComboBox->currentData().toString();
    QString name = ui->nameLineEdit->text().trimmed();
    QString email = ui->emailLineEdit->text().trimmed();
    QString address = ui->addressLineEdit->text().trimmed();
    QString phone = ui->phoneNumberLineEdit->text().trimmed();
    QString dob = ui->dateOfBirthDateEdit->text().trimmed();

        QSqlQuery query(db);
        query.prepare("UPDATE users set gender = ?, name = ?, email = ?, address = ?, phone = ?, dob = ? where username = ?");
        query.addBindValue(gender);
        query.addBindValue(name);
        query.addBindValue(email);
        query.addBindValue(address);
        query.addBindValue(phone);
        query.addBindValue(dob);
        query.addBindValue(g_username);
        if(query.exec()){
            QMessageBox::information(this, "Success", "Successfully updated the information");
        }
        else{
            qDebug() << query.lastError();
        }



}

