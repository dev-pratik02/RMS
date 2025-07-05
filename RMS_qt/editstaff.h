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

private:
    Ui::editstaff *ui;
};

#endif // EDITSTAFF_H
