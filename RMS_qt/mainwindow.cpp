#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrorders = new orders();
}

MainWindow::~MainWindow()
{
    delete ptrorders;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ptrorders->show();
}

