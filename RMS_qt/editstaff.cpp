#include "editstaff.h"
#include "ui_editstaff.h"

editstaff::editstaff(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::editstaff)
{
    ui->setupUi(this);

    connect(ui->SAVE, &QPushButton::clicked, this, &editstaff::accept);
    connect(ui->CANCEL, &QPushButton::clicked, this, &editstaff::reject);
}

editstaff::~editstaff()
{
    delete ui;
}

void editstaff::setData(const QString &id, const QString &name, const QString &position,
                        const QString &salary, const QString &age, const QString &contact)
{
    staffId = id;
    ui->input_id->setText(id);
    ui->input_name->setText(name);
    ui->input_position->setText(position);
    ui->input_salary->setText(salary);
    ui->input_age->setText(age);
    ui->input_contact->setText(contact);
}

QString editstaff::getId() const {
    return staffId;
}

QString editstaff::getName() const {
    return ui->input_name->text();
}

QString editstaff::getPosition() const {
    return ui->input_position->text();
}

QString editstaff::getSalary() const {
    return ui->input_salary->text();
}

QString editstaff::getAge() const {
    return ui->input_age->text();
}

QString editstaff::getContact() const {
    return ui->input_contact->text();
}
