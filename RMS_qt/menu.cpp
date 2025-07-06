#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    ptraddmenuitem = new addmenuitem();
}

menu::~menu()
{
    delete ui;
}

void menu::on_ADDMENITEMS_clicked()
{
    ptraddmenuitem->show();
}

