#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrstaff = new staff();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ptrstaff;
}

void MainWindow::on_pushButton_clicked()
{
    ptrstaff->show();
}

