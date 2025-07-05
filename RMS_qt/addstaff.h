#ifndef ADDSTAFF_H
#define ADDSTAFF_H

#include <QDialog>

namespace Ui {
class addstaff;
}

class addstaff : public QDialog
{
    Q_OBJECT

public:
    explicit addstaff(QWidget *parent = nullptr);
    ~addstaff();

private:
    Ui::addstaff *ui;
};

#endif // ADDSTAFF_H
