#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    if(!ptrmenu){
        ptrmenu = new menu();
    }
    ptrmenu->show();
}


void MainWindow::on_btn_staff_clicked()
{
    if(!ptrstaff){
        ptrstaff = new staff();
    }
    ptrstaff->show();
}


void MainWindow::on_btn_tables_clicked()
{
    if(!ptrtables){
        ptrtables = new table();
    }
    ptrtables->show();
}


void MainWindow::on_btn_orders_clicked()
{
    if(!ptrorders){
        ptrorders = new orders();
    }
    ptrorders->show();
}


void MainWindow::on_btn_pos_clicked()
{
    if(!ptrpos){
        ptrpos = new class pos();
    }
    ptrpos->show();
}

