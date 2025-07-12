#ifndef FORGOTPASS_H
#define FORGOTPASS_H

#include <QDialog>

namespace Ui {
class forgotpass;
}

class forgotpass : public QDialog
{
    Q_OBJECT

public:
    explicit forgotpass(QWidget *parent = nullptr);
    ~forgotpass();

private:
    Ui::forgotpass *ui;

private slots:
    void on_btn_confirm_clicked();

};

#endif // FORGOTPASS_H
