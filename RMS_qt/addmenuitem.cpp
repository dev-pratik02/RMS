#include "addmenuitem.h"
#include "ui_addmenuitem.h"

addmenuitem::addmenuitem(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addmenuitem)
{
    ui->setupUi(this);
}

addmenuitem::~addmenuitem()
{
    delete ui;
}
