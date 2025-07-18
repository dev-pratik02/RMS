#ifndef EDITMENUITEM_H
#define EDITMENUITEM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include "databasemanager.h"
namespace Ui {
class editmenuitem;
}

class editmenuitem : public QDialog
{
    Q_OBJECT

public:
    explicit editmenuitem(QString id, QString name, QString price,QString description,QString category, QWidget *parent = nullptr);
    ~editmenuitem();

signals:
    void dataUpdated();

private slots:
    void on_btn_save_clicked();
    void on_btn_reset_clicked();
    void on_image_upload_clicked();

private:
    Ui::editmenuitem *ui;
    QString itemId;
    QSqlDatabase db;
};


#endif
