#include "forgotpass.h"
#include "ui_forgotpass.h"

forgotpass::forgotpass(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::forgotpass)
{
    ui->setupUi(this);
}

forgotpass::~forgotpass()
{
    delete ui;
}
