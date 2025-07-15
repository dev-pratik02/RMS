#ifndef EDITSTAFF_H
#define EDITSTAFF_H

#include <QDialog>

namespace Ui {
class editstaff;
}

class editstaff : public QDialog
{
    Q_OBJECT

public:
    explicit editstaff(QWidget *parent = nullptr);
    ~editstaff();

    void setData(const QString &id, const QString &name, const QString &position,
                 const QString &salary, const QString &age, const QString &contact);

    QString getId() const;
    QString getName() const;
    QString getPosition() const;
    QString getSalary() const;
    QString getAge() const;
    QString getContact() const;

private:
    Ui::editstaff *ui;
    QString staffId;
};

#endif // EDITSTAFF_H
