#ifndef EDIT_ORDER_H
#define EDIT_ORDER_H

#include <QDialog>

namespace Ui {
class edit_order;
}

class edit_order : public QDialog
{
    Q_OBJECT

public:
    explicit edit_order(QWidget *parent = nullptr);
    edit_order(const QString &orderId, const QString &table, const QString &time, const QString &status,
               const QList<QList<QString>> &items, QWidget *parent = nullptr);
    ~edit_order();

private:
    Ui::edit_order *ui;
    QString m_orderId, m_table, m_time, m_status;
    QList<QList<QString>> m_items;
};

#endif // EDIT_ORDER_H
