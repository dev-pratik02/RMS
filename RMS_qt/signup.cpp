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

void setupEyeButton(QLineEdit *passwordEdit);

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

    QString hashed = hashPassword("mypassword");
    setupEyeButton(ui->line_password);
    setupEyeButton(ui->line_confirmpass);
    qDebug() << "line_password valid:" << ui->line_password;
    qDebug() << "line_confirmpass valid:" << ui->line_confirmpass;


    if (!isValidEmail(ui->line_email->text())) {
        // show warning
    }

}
class ResizeFilter : public QObject {
public:
    QToolButton *button;
    QLineEdit *lineEdit;
    int frameWidth;
    int buttonWidth;

    ResizeFilter(QToolButton *btn, QLineEdit *le, int fw, int bw)
        : QObject(le), button(btn), lineEdit(le), frameWidth(fw), buttonWidth(bw) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj == lineEdit && event->type() == QEvent::Resize) {
            button->setGeometry(
                lineEdit->rect().right() - buttonWidth - frameWidth,
                (lineEdit->rect().height() - button->sizeHint().height()) / 2,
                buttonWidth,
                button->sizeHint().height()
                );
        }
        return QObject::eventFilter(obj, event);
    }
};

signup::~signup()
{
    delete ui;
}

bool signup::openDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Swift/RMS/RMS_qt/RmsApp.db");

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

    if (name.isEmpty() || phone.isEmpty() || email.isEmpty() || pass.isEmpty() || confirmpass.isEmpty()) {
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
    query.prepare("INSERT INTO users (name, phone, email, dob, password) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(phone);
    query.addBindValue(email);
    query.addBindValue(dob);
    query.addBindValue(hashedPass);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Signup successful!");
        this->close();
    }

    QSqlDatabase::database().close();
}

void setupEyeButton(QLineEdit *passwordEdit) {
    // Set echo mode to Password
    passwordEdit->setEchoMode(QLineEdit::Password);

    // Create eye button
    QToolButton *eyeButton = new QToolButton(passwordEdit);
    QPixmap pixmap("C:/Users/Swift/RMS/RMS-assets/eye.png");

    if (pixmap.isNull()) {
        qDebug() << "Eye image not found.";
    } else {
        eyeButton->setIcon(QIcon(pixmap));
    }

    eyeButton->setCursor(Qt::PointingHandCursor);
    eyeButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");

    // Adjust margins to make space for the button
    int frameWidth = passwordEdit->style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    int buttonWidth = eyeButton->sizeHint().width();
    passwordEdit->setTextMargins(0, 0, buttonWidth + frameWidth, 0);

    // Position button inside the QLineEdit
    eyeButton->setGeometry(
        passwordEdit->rect().right() - buttonWidth - frameWidth,
        (passwordEdit->rect().height() - eyeButton->sizeHint().height()) / 2,
        buttonWidth,
        eyeButton->sizeHint().height()
        );
    eyeButton->show();

    // Handle press to show password
    QObject::connect(eyeButton, &QToolButton::pressed, [=]() {
        passwordEdit->setEchoMode(QLineEdit::Normal);
    });

    QObject::connect(eyeButton, &QToolButton::released, [=]() {
        passwordEdit->setEchoMode(QLineEdit::Password);
    });

    // Reposition on resize
    QObject::connect(passwordEdit, &QLineEdit::textChanged, [=]() {
        eyeButton->setGeometry(
            passwordEdit->rect().right() - buttonWidth - frameWidth,
            (passwordEdit->rect().height() - eyeButton->sizeHint().height()) / 2,
            buttonWidth,
            eyeButton->sizeHint().height()
            );
    qDebug() << "Setting up eye button for" << passwordEdit->objectName();

    });
    ResizeFilter *filter = new ResizeFilter(eyeButton, passwordEdit, frameWidth, buttonWidth);
    passwordEdit->installEventFilter(filter);
}
