#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrorders = new orders();

    DB_connection= QSqlDatabase::addDatabase("QSQLITE");
    DB_connection.setDatabaseName("/Users/pratik/Programming/RMS/RmsApp.db");
    if(DB_connection.open()){
        qDebug() <<"Database is connected";
    }
    else{
        qDebug() << "Database connection failed" ;
        qDebug() << "Error:"<< DB_connection.lastError();
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ptrorders->show();
}

