#include "signup.h"
#include "ui_signup.h"

signup::signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signup)
{
    ui->setupUi(this);
}
#include "signup.h"

signup::~signup()
{
    delete ui;
}
