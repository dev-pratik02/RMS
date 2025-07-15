#ifndef ADDSTAFF_H
#define ADDSTAFF_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class addstaff;
}

class addstaff : public QDialog
{
    Q_OBJECT

public:
    explicit addstaff(QWidget *parent = nullptr);
    ~addstaff();

private slots:
    void on_btn_add_clicked();
    void on_btn_reset_clicked();

private:
    Ui::addstaff *ui;
    QSqlDatabase db;
};

#endif // ADDSTAFF_H
