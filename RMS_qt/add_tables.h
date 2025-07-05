#ifndef ADD_TABLES_H
#define ADD_TABLES_H

#include <QDialog>
class edit;
namespace Ui {
class add_tables;
}

class add_tables : public QDialog
{
    Q_OBJECT

public:
    explicit add_tables(edit* editPagePtr,QWidget *parent = nullptr);
    ~add_tables();
private slots:
    void on_btn_back1_clicked();
    void on_btn_reset_clicked();
    void on_btn_save_clicked();
private:
    Ui::add_tables *ui;
    edit* editPage;
};

#endif // ADD_TABLES_H
