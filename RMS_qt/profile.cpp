#include "profile.h"
#include "ui_profile.h"

profile::profile(QWidget *parent, MainWindow *mainWindow)
    : QDialog(parent)
    , ui(new Ui::profile), m_mainWindow(mainWindow)
{
    ui->setupUi(this);


    load_data();

    ui->roleLineEdit->setReadOnly(true);
}

profile::~profile()
{
    delete ui;
}

void profile::load_data(){
    QSqlDatabase &db = DatabaseManager::getDatabase();

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";
    }

    QSqlQuery load(db);
    load.prepare("SELECT gender,name,email,address,phone,dob,role from users where username = ?");
    load.addBindValue(g_username);
    if(load.exec()){
        while(load.next()){
            ui->maleComboBox->setCurrentIndex(0);
            ui->nameLineEdit->setText(load.value(1).toString());
            ui->emailLineEdit->setText(load.value(2).toString());
            ui->addressLineEdit->setText(load.value(3).toString());
            ui->phoneNumberLineEdit->setText(load.value(4).toString());

            QString dobStr = load.value(5).toString();
            qDebug() << "DOB as string:" << dobStr;
            QDate dob = QDate::fromString(dobStr, "dd/MM/yyyy");  // Match the format in DB
            ui->dateOfBirthDateEdit->setDate(dob);

            ui->roleLineEdit->setText(load.value(6).toString());

        }
    }
}
void profile::on_logout_btn_clicked()
{
    g_userRole = "";
    g_username = "";
    if (m_mainWindow) {
        m_mainWindow->close();  // closes the main window
    }
    login_page *main = new login_page();
    main->show();
    this->close();

}


void profile::on_pass_btn_clicked()
{
    if(!passPage){
        passPage = new change_password();
    }
    passPage->show();
}


void profile::on_btn_reset_clicked()
{
    load_data();
}


void profile::on_btn_save_clicked()
{
    QString gender = ui->maleComboBox->currentText();
    QString name = ui->nameLineEdit->text().trimmed();
    QString email = ui->emailLineEdit->text().trimmed();
    QString address = ui->addressLineEdit->text().trimmed();
    QString phone = ui->phoneNumberLineEdit->text().trimmed();
    QString dob = ui->dateOfBirthDateEdit->text().trimmed();

    qDebug() << "the gender is : " << gender;
    qDebug() << "dob:" << dob;
    if(name.isEmpty() || email.isEmpty() || address.isEmpty() || phone.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Please fill all the fields");
        return;

    }

    if(!isOver18(dob)){
        QMessageBox::critical(this, "Error", "Enter valid date of birth");
        return;
    }

    if(isValidEmail(email)){
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
            on_btn_reset_clicked();
            this->close();
        }
        else{
            qDebug() << query.lastError();
        }

    }
    else{
        QMessageBox::critical(this, "Error", "Please provide valid email");

    }

}

