#include "menuiteminfo.h"
#include "ui_menuiteminfo.h"

menuiteminfo::menuiteminfo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::menuiteminfo)
{
    ui->setupUi(this);
}

menuiteminfo::~menuiteminfo()
{
    delete ui;
}
