#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
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
    void on_ADDMENITEMS_clicked();

private:
    Ui::menu *ui;
    addmenuitem *ptraddmenuitem;
};

#endif // MENU_H
