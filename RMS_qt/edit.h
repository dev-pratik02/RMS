#ifndef EDIT_H
#define EDIT_H

#include <QDialog>

namespace Ui {
class edit;
}

class edit : public QDialog
{
    Q_OBJECT

public:
    explicit edit(QWidget *parent = nullptr);
    ~edit();
private slots:
    void on_btn_back_clicked();
    void on_btn_add_clicked();
private:
    Ui::edit *ui;
};

#endif // EDIT_H
