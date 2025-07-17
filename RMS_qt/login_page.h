#ifndef LOGIN_PAGE_H
#define LOGIN_PAGE_H

#include <QDialog>

namespace Ui {
class login_page;
}

class login_page : public QDialog
{
    Q_OBJECT

private slots:

    void on_btn_login_clicked();

    void on_btn_signup_clicked();

    void on_btn_forgot_clicked();

private:
     Ui::login_page *ui;
     bool passwordVisible = false;
     void setupEyeButtone();

public:

    explicit login_page(QWidget *parent = nullptr);
    ~login_page();

};



#endif // LOGIN_PAGE_H
