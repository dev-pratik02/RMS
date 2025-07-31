#include "editstaff.h"
#include "ui_editstaff.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QMessageBox>

editstaff::editstaff(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::editstaff)
{
    ui->setupUi(this);

    // 🔒 Make ID field non-editable
    ui->input_id->setReadOnly(true);

    // Validators
    ui->input_age->setValidator(new QIntValidator(18, 99, this));
    ui->input_salary->setValidator(new QDoubleValidator(0, 1000000, 2, this));

    QRegularExpression phoneRegex("^\\d{10}$");
    ui->input_contact->setValidator(new QRegularExpressionValidator(phoneRegex, this));

    QRegularExpression namePositionRegex("^[a-zA-Z\\s]*$");
    ui->input_name->setValidator(new QRegularExpressionValidator(namePositionRegex, this));
    ui->input_position->setValidator(new QRegularExpressionValidator(namePositionRegex, this));

    // SAVE
    connect(ui->SAVE, &QPushButton::clicked, this, [this]() {
        QString name = ui->input_name->text().trimmed();
        QString position = ui->input_position->text().trimmed();
        QString salary = ui->input_salary->text().trimmed();
        QString age = ui->input_age->text().trimmed();
        QString contact = ui->input_contact->text().trimmed();

        if (name.isEmpty() || position.isEmpty() || salary.isEmpty() ||
            age.isEmpty() || contact.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please fill all fields correctly.");
            return;
        }

        if (contact.length() != 10) {
            QMessageBox::warning(this, "Input Error", "Contact number must be exactly 10 digits.");
            return;
        }

        accept();
    });

    // CANCEL
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
    return ui->input_name->text().trimmed();
}

QString editstaff::getPosition() const {
    return ui->input_position->text().trimmed();
}

QString editstaff::getSalary() const {
    return ui->input_salary->text().trimmed();
}

QString editstaff::getAge() const {
    return ui->input_age->text().trimmed();
}

QString editstaff::getContact() const {
    return ui->input_contact->text().trimmed();
}
