#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrorders = new orders();
    ptrpos = new class pos();
    ptrmenu = new menu();
    ptrstaff = new staff();
    ptrtables = new table();
}

MainWindow::~MainWindow()
{
    delete ptrorders;
    delete ptrpos;
    delete ptrmenu;
    delete ptrstaff;
    delete ptrtables;
    delete ui;
}



void MainWindow::on_btn_menu_clicked()
{
    ptrmenu->show();
}


void MainWindow::on_btn_staff_clicked()
{
    ptrstaff->show();
}


void MainWindow::on_btn_tables_clicked()
{
    ptrtables->show();
}


void MainWindow::on_btn_orders_clicked()
{
    ptrorders->show();
}


void MainWindow::on_btn_pos_clicked()
{
    ptrpos->show();
}

