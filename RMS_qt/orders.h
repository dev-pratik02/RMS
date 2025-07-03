#ifndef ORDERS_H
#define ORDERS_H

#include <QDialog>

namespace Ui {
class orders;
}

class orders : public QDialog
{
    Q_OBJECT

public:
    explicit orders(QWidget *parent = nullptr);
    ~orders();

private:
    Ui::orders *ui;
};

#endif // ORDERS_H
