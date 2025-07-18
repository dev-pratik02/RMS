#ifndef ADDMENUITEM_H
#define ADDMENUITEM_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QPixmap>
#include <QFileDialog>

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
    void on_btn_save_clicked();
    void on_btn_reset_clicked();
    void on_image_upload_clicked();

private:
    Ui::addmenuitem *ui;
    QSqlDatabase db;
};

#endif
