#include "addstaff.h"
#include "ui_addstaff.h"

addstaff::addstaff(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addstaff)
{
    ui->setupUi(this);
}

addstaff::~addstaff()
{
    delete ui;
}



void addstaff::on_btn_reset_clicked()
{

}


void addstaff::on_btn_add_clicked()
{

}

