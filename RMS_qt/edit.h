#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <QSqlDatabase>
#include "add_tables.h"
#include <QSqlQuery>
#include <QTableWidgetItem>
#include<editing_table.h>
namespace Ui {
class edit;
}

class edit : public QDialog
{
    Q_OBJECT

public:
    explicit edit(QWidget *parent = nullptr);
    ~edit();

private:
    Ui::edit *ui;
    QSqlDatabase db;
    add_tables *addPage;
    void refreshTableView();
    void loadTableView();

    editing_table* editForm;

private slots:
    void on_btn_back_clicked();
    void on_btn_add_clicked();
    void on_edit_button_clicked(int row);

    void on_delete_button_clicked();


};

#endif
