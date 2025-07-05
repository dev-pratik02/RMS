#include "add_tables.h"
#include "ui_add_tables.h"
#include "edit.h"
#include <QMessageBox>
add_tables::add_tables(edit *editPagePtr,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add_tables)
    , editPage(editPagePtr)
{
    ui->setupUi(this);
    connect(ui->btn_back1, &QPushButton::clicked, this, &add_tables::on_btn_back1_clicked);
    connect(ui->btn_reset, &QPushButton::clicked, this, &add_tables::on_btn_reset_clicked);
    connect(ui->btn_save, &QPushButton::clicked, this, &add_tables::on_btn_save_clicked);
}

add_tables::~add_tables()
{
    delete ui;
}
void add_tables::on_btn_back1_clicked()
{
    this->hide();
    editPage->show();
}
void add_tables::on_btn_reset_clicked()
{
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->comboBox_1->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);

    // Clear QTextEdit
    ui->textEdit_1->clear();
}

void add_tables::on_btn_save_clicked()
{
    // Validate inputs
    if (ui->lineEdit_1->text().isEmpty() ||
        ui->lineEdit_2->text().isEmpty() ||
        ui->comboBox_1->currentIndex() == 0 ||
        ui->comboBox_2->currentIndex() == 0 ||
        ui->comboBox_3->currentIndex() == 0 ||
        ui->textEdit_1->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "Missing Fields", "Please complete all fields before saving.");
        return;
    }

    QMessageBox::information(this, "Success", "Saved successfully!");
}
