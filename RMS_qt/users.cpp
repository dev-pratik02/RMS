#include "users.h"
#include "ui_users.h"

users::users(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::users)
{
    ui->setupUi(this);

    ui->table_users->clearContents();
    ui->table_users->setRowCount(0);
    QSqlDatabase &db = DatabaseManager::getDatabase();
    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError();
    }

    QSqlQuery query(db);
    query.prepare("SELECT name,address,phone,email,dob,username,role FROM users");
    int row=0;
    if(query.exec()){
        while(query.next()){
            QString name = query.value(0).toString();
            QString address = query.value(1).toString();
            QString phone = query.value(2).toString();
            QString email = query.value(3).toString();
            QString dob = query.value(4).toString();
            QString username = query.value(5).toString();
            QString role = query.value(6).toString();

            ui->table_users->insertRow(row);
            ui->table_users->setItem(row, 0, new QTableWidgetItem(name));
            ui->table_users->setItem(row, 1, new QTableWidgetItem(address));
            ui->table_users->setItem(row, 2, new QTableWidgetItem(phone));
            ui->table_users->setItem(row, 3, new QTableWidgetItem(email));
            ui->table_users->setItem(row, 4, new QTableWidgetItem(dob));
            ui->table_users->setItem(row, 5, new QTableWidgetItem(username));
            ui->table_users->setItem(row, 6, new QTableWidgetItem(role));
            row++;
        }
    }
    else{
        qDebug() << "Could not execute query to load data in users table \n " << query.lastError();
    }
}

users::~users()
{
    delete ui;
}

void users::on_btn_adduser_clicked()
{
    ptrsignup = new signup();
    ptrsignup->show();
    this->close();
}
