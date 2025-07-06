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





