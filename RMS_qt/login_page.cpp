#include "login_page.h"
#include "ui_login_page.h"

login_page::login_page(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login_page)
{
    ui->setupUi(this);
}

login_page::~login_page()
{
    delete ui;
}
