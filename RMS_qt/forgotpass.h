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


private slots:
    void on_btn_confirm_clicked();

    void on_btn_reset_clicked();

private:
    Ui::forgotpass *ui;
    bool passwordVisible = false;
    void setupEyeButtone();


};

#endif // FORGOTPASS_H
