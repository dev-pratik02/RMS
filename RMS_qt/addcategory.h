#ifndef ADDCATEGORY_H
#define ADDCATEGORY_H

#include <QDialog>
#include <QtSql>
#include "databasemanager.h"
namespace Ui {
class addcategory;
}

class addcategory : public QDialog
{
    Q_OBJECT

public:
    explicit addcategory(QWidget *parent = nullptr);
    ~addcategory();

private slots:
    void on_btn_add_clicked();
    void on_btn_reset_clicked();

private:
    Ui::addcategory *ui;
    QSqlDatabase db;

signals:
    void categoryUpdated();

public:
    void setValues(QString name, QString itemCount, QString description);

};

#endif // ADDCATEGORY_H
