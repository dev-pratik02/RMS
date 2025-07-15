#ifndef ADD_TABLES_H
#define ADD_TABLES_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class add_tables;
}

class add_tables : public QDialog
{
    Q_OBJECT

public:
    explicit add_tables(QWidget *parent = nullptr);
    ~add_tables();

signals:
    void dataSaved();

private:
    Ui::add_tables *ui;
    QSqlDatabase db;

public:
    // void setNextTableNumber();

private slots:
    void on_btn_save_clicked();
    void on_btn_reset_clicked();
    void on_btn_back1_clicked();
};

#endif
