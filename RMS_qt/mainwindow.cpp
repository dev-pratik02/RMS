#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ptrlogin = new login_page();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_login_clicked()
{
    ptrlogin->show();
}
void MainWindow ::on_btn_signup_clicked()
{
    signup signupDialog(this);
    signupDialog.exec();
}
