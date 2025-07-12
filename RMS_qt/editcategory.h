#ifndef EDITCATEGORY_H
#define EDITCATEGORY_H

#include <QDialog>

namespace Ui {
class editcategory;
}

class editcategory : public QDialog
{
    Q_OBJECT

public:
    explicit editcategory(QString name, QString id, QString itemCount, QString description, QWidget *parent = nullptr);
    ~editcategory();

private slots:
    void on_btn_edit_clicked();
    void on_btn_reset_clicked();


private:
    Ui::editcategory *ui;
    QString originalId;

signals:
    void categoryUpdated();
};


#endif // EDITCATEGORY_H
