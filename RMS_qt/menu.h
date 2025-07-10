#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "editmenuitem.h"
#include "addmenuitem.h"

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
    void handleEditButton(QString,QString,QString,QString);  // custom slot

private:
    Ui::menu *ui;
    addmenuitem *ptraddmenuitem;
private:
    void connectDatabase();
    void loadDataIntoTable();
    QVector<QPushButton*> editButtons;  // store buttons if needed

};

#endif
