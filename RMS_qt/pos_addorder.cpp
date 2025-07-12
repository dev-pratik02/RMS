#include "pos_addorder.h"
#include "ui_pos_addorder.h"

pos_addorder::pos_addorder(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pos_addorder)
{
    ui->setupUi(this);
}

pos_addorder::pos_addorder(QString table_no,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pos_addorder)
{
    ui->setupUi(this);
    qDebug() << "Received table no.:" << table_no;
}

pos_addorder::~pos_addorder()
{
    delete ui;
}
