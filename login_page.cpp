#include "login_page.h"
#include "ui_login_page.h"

login_page::login_page(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login_page)
{

    ui->setupUi(this);

    // First image
    QPixmap loginPix("C:/Users/VICTUS/OneDrive/Desktop/badal/RMS-assets/login_page_image.png");
    if(!loginPix.isNull()) {
        ui->label_pic->setPixmap(loginPix);
        ui->label_pic->setScaledContents(true);  // Optional: Scale to fit
    } else {
        qDebug() << "Failed to load login image";
    }

    // Second image (use different variable name)
    QPixmap hatPix("C:/Users/VICTUS/OneDrive/Desktop/badal/RMS-assets/login_page_chefHat.png");
    if(!hatPix.isNull()) {
        ui->label_pic1->setPixmap(hatPix);
        ui->label_pic1->setScaledContents(true);  // Optional: Scale to fit
    } else {
        qDebug() << "Failed to load chef hat image";
    }
}

login_page::~login_page()
{
    delete ui;
}
