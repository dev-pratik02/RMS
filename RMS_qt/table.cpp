#include "table.h"
#include "ui_table.h"
#include<edit.h>

table::table(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::table)
    , editpage(nullptr)
{
    ui->setupUi(this);
    connect(ui->btn_edit, &QPushButton::clicked, this, &table::on_btn_edit_clicked);

}

table::~table()
{
    delete ui;
}
void table::on_btn_edit_clicked()
{
    this->hide();
    if (!editpage) {
        editpage = new edit(this);
    }

    editpage->show();
}
