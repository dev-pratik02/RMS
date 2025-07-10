#include "editmenuitem.h"
#include "ui_editmenuitem.h"

editmenuitem::editmenuitem(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::editmenuitem)
{
    ui->setupUi(this);
}


editmenuitem::editmenuitem(QString id, QString name, QString price,QString description, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editmenuitem)
{
    ui->setupUi(this);

    ui->item_name->setText(name);
    ui->item_price->setText(price);
    ui->item_description->setPlainText(description);
}



editmenuitem::~editmenuitem()
{
    delete ui;
}
