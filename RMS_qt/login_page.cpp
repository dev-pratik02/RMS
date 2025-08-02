#include "login_page.h"
#include "ui_login_page.h"
#include "utils.h"
#include "signup.h"
#include "forgotpass.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QToolButton>
#include <QStyle>
#include "databasemanager.h"
#include "mainwindow.h"
#include "globals.h"

login_page::login_page(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login_page)
{
    ui->setupUi(this);
    ui->input_password->setEchoMode(QLineEdit::Password);
    setupEyeButton(ui->input_password);

    // First image
    QPixmap loginPix(":/login_page/login_page_image.png");
    if(!loginPix.isNull()) {
        ui->label_pic->setPixmap(loginPix);
        ui->label_pic->setScaledContents(true);
    } else {
        qDebug() << "Failed to load login image";
    }

    // Second image (use different variable name)
    QPixmap hatPix(":/login_page/login_page_chefHat.png");
    if(!hatPix.isNull()) {
        ui->label_pic1->setPixmap(hatPix);
        ui->label_pic1->setScaledContents(true);
    } else {
        qDebug() << "Failed to load chef hat image";
    }

}


login_page::~login_page()
{
    delete ui;
}

void login_page::on_btn_login_clicked()
{
    QString userid = ui->input_userid->text().trimmed();
    QString password = ui->input_password->text();

    // Validation check
    if (userid.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter both User ID and Password.");
        return;
    }

    // Open Database
    QSqlDatabase &db = DatabaseManager::getDatabase();


    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
        return;
    }
    QString hashedInput = hashPassword(password);
    // qDebug() << hashedInput;
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM users WHERE username = ? AND password = ?");
    query.addBindValue(userid);
    query.addBindValue(hashedInput);

    if (query.exec()) {

        if (query.next() && query.value(0).toInt() > 0) {
            QMessageBox::information(this, "Login Success", "Welcome back!");

            //To get the role of the user
            g_username = userid;
            QSqlQuery role(db);
            role.prepare("SELECT role FROM users WHERE username=? AND password=?");
            role.addBindValue(userid);
            role.addBindValue(hashedInput);
            if(role.exec()){
                while(role.next()){
                    g_userRole = role.value(0).toString();
                    qDebug() << "The role of the user is " << g_userRole;
                }
            }
            else{
                qDebug() << "Role could not be found \n" << role.lastError();
            }
            MainWindow *main = new MainWindow();
            main->show();
            this->close();
        } else {
            QMessageBox::warning(this, "Login Failed", "Invalid User ID or Password.");
        }
    } else {
        QMessageBox::critical(this, "Query Error", query.lastError().text());
    }
}


void login_page::on_btn_forgot_clicked()
{
    forgotpass forgotDialog(this);
    forgotDialog.exec();
}

