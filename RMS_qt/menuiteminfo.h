#ifndef MENUITEMINFO_H
#define MENUITEMINFO_H

#include <QDialog>

namespace Ui {
class menuiteminfo;
}

class menuiteminfo : public QDialog
{
    Q_OBJECT

public:
    explicit menuiteminfo(QWidget *parent = nullptr);
    ~menuiteminfo();

private:
    Ui::menuiteminfo *ui;
};

#endif // MENUITEMINFO_H
