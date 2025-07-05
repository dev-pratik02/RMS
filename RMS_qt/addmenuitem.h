#ifndef ADDMENUITEM_H
#define ADDMENUITEM_H

#include <QDialog>

namespace Ui {
class addmenuitem;
}

class addmenuitem : public QDialog
{
    Q_OBJECT

public:
    explicit addmenuitem(QWidget *parent = nullptr);
    ~addmenuitem();

private:
    Ui::addmenuitem *ui;
};

#endif // ADDMENUITEM_H
