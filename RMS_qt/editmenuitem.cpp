#include "editmenuitem.h"
#include "ui_editmenuitem.h"

editmenuitem::editmenuitem(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::editmenuitem)
{
    ui->setupUi(this);
}

editmenuitem::~editmenuitem()
{
    delete ui;
}
