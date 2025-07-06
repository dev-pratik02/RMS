#include "staff.h"
#include "ui_staff.h"

staff::staff(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::staff)
{
    ui->setupUi(this);

    ptraddstaff = new addstaff();
}

staff::~staff()
{
    delete ui;
}

void staff::on_ADDSTAFF_clicked()
{
    ptraddstaff->show();
}

