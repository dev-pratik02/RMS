#ifndef EDITMENUITEM_H
#define EDITMENUITEM_H

#include <QDialog>

namespace Ui {
class editmenuitem;
}

class editmenuitem : public QDialog
{
    Q_OBJECT

public:
    explicit editmenuitem(QWidget *parent = nullptr);
    explicit editmenuitem(QString id, QString name, QString price,QString description, QWidget *parent = nullptr);
    ~editmenuitem();

private:
    Ui::editmenuitem *ui;
};

#endif // EDITMENUITEM_H
