#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrmenu = new menu();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ptrmenu;
}

void MainWindow::on_pushButton_clicked()
{
    ptrmenu->show();
}

