#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "addmenuitem.h"
#include "category.h"
#include <QtSql>
namespace Ui {
class menu;
}

class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_btn_addmenu_clicked();
    void on_btn_category_clicked();
    void on_btn_edit_clicked();
    void loadData();
    void handleEditButton(QString,QString,QString,QString, QString);
    void handleDeleteButton(QString id);


private:
    Ui::menu *ui;
    addmenuitem *ptraddmenuitem;
    QSqlDatabase db;
    void connectDatabase();
    void loadDataIntoTable();
    QVector<QPushButton*> editButtons;

};

#endif
