#include "editstaff.h"
#include "ui_editstaff.h"

editstaff::editstaff(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::editstaff)
{
    ui->setupUi(this);
}

editstaff::~editstaff()
{
    delete ui;
}
