#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QtSql>
namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_btn_confirm_clicked();


private:
    Ui::signup *ui;
    QSqlDatabase db;
    bool passwordVisible = false;
    void setupEyeButtone();
};

#endif // SIGNUP_H
