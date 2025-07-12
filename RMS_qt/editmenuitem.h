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
    explicit editmenuitem(QString id, QString name, QString price,QString description, QWidget *parent = nullptr);
    ~editmenuitem();

signals:
    void dataUpdated();

private slots:
    void on_btn_save_clicked();
    void on_btn_reset_clicked();


private:
    Ui::editmenuitem *ui;
    QString itemId;
};


#endif
