#include "category.h"
#include "ui_category.h"
#include "addcategory.h"
#include "editcategory.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QHBoxLayout>

#include "databasemanager.h"


category::category(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::category)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnWidth(0, 150);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 250);
    ui->tableWidget->setColumnWidth(4, 150);
    loadCategories();


    QSqlDatabase &db = DatabaseManager::getDatabase();


    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";
    }
}


category::~category()
{
    delete ui;
}




void category::on_btn_addcategory_clicked()
{
    addcategory addDialog(this);
    if (addDialog.exec() == QDialog::Accepted) {
        loadCategories();

    }
}

void category::loadCategories()
{
    QSqlQuery query(db);
    query.prepare("SELECT [category_name], [category_id], [display_order], [description] FROM category");

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(5);

    int row = 0;
    if(query.exec()){
        while (query.next()) {
            QString name = query.value(0).toString();
            QString id = query.value(1).toString();
            QString itemCount = query.value(2).toString();
            QString description = query.value(3).toString();

            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(id));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(itemCount));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(description));

            QWidget *actionWidget = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(actionWidget);
            layout->setContentsMargins(0, 0, 0, 0);

            QPushButton *editBtn = new QPushButton("Edit");
            connect(editBtn, &QPushButton::clicked, this, [=]() {
                handleEditCategory(name, id, itemCount, description);
            });
            layout->addWidget(editBtn);

            QPushButton *deleteBtn = new QPushButton("Delete");
            connect(deleteBtn, &QPushButton::clicked, this, [=]() {
                handleDeleteCategory(id);
            });
            layout->addWidget(deleteBtn);

            ui->tableWidget->setCellWidget(row, 4, actionWidget);
            row++;
        }
    }
    else{
        qDebug() << "Could not execute the query \n " << query.lastError();
    }

    QStringList headers = {"Category Name", "Category ID", "Display Order", "Description", "Actions"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void category::handleEditCategory(QString name, QString id, QString itemCount, QString description)
{
    editcategory *editWin = new editcategory(name, id, itemCount, description, this);
    connect(editWin, &editcategory::categoryUpdated, this, [=]() {
        loadCategories();
    });
    editWin->exec();
}

void category::handleDeleteCategory(QString id)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM category WHERE [category_id] = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Deleted", "Category deleted successfully.");

    QSqlQuery querySeq(db);
    querySeq.prepare("UPDATE sqlite_sequence SET seq = (SELECT MAX(category_id) FROM category) WHERE name = 'category'");
    if(querySeq.exec()){
        qDebug() << "updated seq of category successfully";
        querySeq.finish();
    }
    else{
        qDebug() << "could not update the seq \n " << querySeq.lastError();
    }

    loadCategories();
}
