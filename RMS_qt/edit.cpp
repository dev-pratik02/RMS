#include "edit.h"
#include "ui_edit.h"
#include<add_tables.h>
edit::edit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit)
{
    ui->setupUi(this);
}

edit::~edit()
{
    delete ui;
}
void edit::on_btn_back_clicked()
{
    this->hide(); // Hide current
    parentWidget()->show();
}
void edit::on_btn_add_clicked()
{
    add_tables *addPage = new add_tables(this);  // 👈 Pass 'this' (pointer to edit page)
    addPage->show();
    this->hide();  // Optional
}
