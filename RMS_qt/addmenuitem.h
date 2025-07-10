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
signals:
    void itemSaved();


private slots:
    void on_btnsave_clicked();

private:
    Ui::addmenuitem *ui;
};

#endif
