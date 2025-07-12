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
};

#endif // FORGOTPASS_H
