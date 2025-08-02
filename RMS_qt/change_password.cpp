#include "change_password.h"
#include "ui_change_password.h"

change_password::change_password(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::change_password)
{
    ui->setupUi(this);

    ui->current_pass->setEchoMode(QLineEdit::Password);
    setupEyeButton(ui->current_pass);
    ui->new_pass->setEchoMode(QLineEdit::Password);
    setupEyeButton(ui->new_pass);
    ui->confirm_pass->setEchoMode(QLineEdit::Password);
    setupEyeButton(ui->confirm_pass);
    ui->btn_reset->setAutoDefault(false);
    ui->btn_save->setDefault(true);
}

change_password::~change_password()
{
    delete ui;
}

void change_password::on_btn_reset_clicked()
{
    ui->current_pass->clear();
    ui->new_pass->clear();
    ui->confirm_pass->clear();
}


void change_password::on_btn_save_clicked()
{
    QString currentPass = ui->current_pass->text();
    QString newPass = ui->new_pass->text();
    QString confirmPass = ui->confirm_pass->text();
    if(newPass != confirmPass){

        QMessageBox::critical(this, "Password mismatch", "The password does not match the confirmed password.");
        on_btn_reset_clicked();
        return;
    }

    if(currentPass.isEmpty() || newPass.isEmpty() || confirmPass.isEmpty()){
        QMessageBox::critical(this, "Could not save", "Please fill all the fields");
    }
    QString hashedInput = hashPassword(currentPass);
    QString hashedPass = hashPassword(newPass);
    QString storedPass;
    QSqlDatabase &db = DatabaseManager::getDatabase();

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return;
    } else {
        qDebug() << "Database connected successfully!";
    }

    QSqlQuery query(db);
    query.prepare("SELECT password FROM users where username = ? ");
    query.addBindValue(g_username);
    if(query.exec()){
        while(query.next()){
            storedPass = query.value(0).toString();
        }
        if(storedPass == hashedInput)
        {
            query.prepare("UPDATE users set password = ? where username = ?");
            query.addBindValue(hashedPass);
            query.addBindValue(g_username);
            if(query.exec()){
                QMessageBox::information(this, "Success", "Password changed successfully.");
                on_btn_reset_clicked();
                this->close();

            }
            else{
                qDebug() << query.lastError();
                QMessageBox::critical(this, "Database Error", query.lastError().text());
            }
        }
    }
    else{
        qDebug() << query.lastError();
        QMessageBox::critical(this, "Database Error", query.lastError().text());

    }
}

