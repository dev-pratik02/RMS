#ifndef POS_ADDORDER_H
#define POS_ADDORDER_H

#include <QDialog>

namespace Ui {
class pos_addorder;
}

class pos_addorder : public QDialog
{
    Q_OBJECT

public:
    explicit pos_addorder(QWidget *parent = nullptr);
    explicit pos_addorder(QString table_no,QWidget *parent = nullptr);
    ~pos_addorder();

private:
    Ui::pos_addorder *ui;
};

#endif // POS_ADDORDER_H
