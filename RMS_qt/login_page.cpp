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


login_page::login_page(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login_page)
{
    ui->setupUi(this);
    setupUiLinks();
    ui->label_signup->setStyleSheet("QLabel { color: blue; text-decoration: underline; }");
    ui->label_forgotpass->setStyleSheet("QLabel { color: blue; text-decoration: underline; }");
    ui->input_password->setEchoMode(QLineEdit::Password);
    setupEyeButton(ui->input_password);

    // First image
    QPixmap loginPix("C:/Users/Swift/RMS/RMS-assets/login_page_image.png");
    if(!loginPix.isNull()) {
        ui->label_pic->setPixmap(loginPix);
        ui->label_pic->setScaledContents(true);
    } else {
        qDebug() << "Failed to load login image";
    }

    // Second image (use different variable name)
    QPixmap hatPix("C:/Users/Swift/RMS/RMS-assets/login_page_chefHat.png");
    if(!hatPix.isNull()) {
        ui->label_pic1->setPixmap(hatPix);
        ui->label_pic1->setScaledContents(true);
    } else {
        qDebug() << "Failed to load chef hat image";
    }

    QString hashed = hashPassword("mypassword");

}


login_page::~login_page()
{
    delete ui;
}
void login_page::setupUiLinks()
{
    ui->label_signup->setText("<a href=\"signup\">Sign up</a>");
    ui->label_forgotpass->setText("<a href=\"forgotpass\">Forgot Password?</a>");

    // Allow link interaction
    ui->label_signup->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label_forgotpass->setTextInteractionFlags(Qt::TextBrowserInteraction);

    ui->label_signup->setOpenExternalLinks(false);
    ui->label_forgotpass->setOpenExternalLinks(false);

    // Connect linkActivated signals
    connect(ui->label_signup, &QLabel::linkActivated, this, &login_page::onSignupClicked);
    connect(ui->label_forgotpass, &QLabel::linkActivated, this, &login_page::onForgotClicked);
}
void login_page::onSignupClicked() {
    signup signupDialog(this);
    signupDialog.exec();
}
void login_page::onForgotClicked() {
    forgotpass forgotDialog(this);
    forgotDialog.exec();
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
    QSqlDatabase db = DatabaseManager::getDatabase();

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
        return;
    }
    QString hashedInput = hashPassword(password);
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE email = ? AND password = ?");
    query.addBindValue(userid);
    query.addBindValue(hashedInput);

    if (query.exec()) {
        if (query.next() && query.value(0).toInt() == 1) {
            QMessageBox::information(this, "Login Success", "Welcome back!");
            this->close();
        } else {
            QMessageBox::warning(this, "Login Failed", "Invalid User ID or Password.");
        }
    } else {
        QMessageBox::critical(this, "Query Error", query.lastError().text());
    }

    db.close();
}
