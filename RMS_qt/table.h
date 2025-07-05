#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
class edit;
namespace Ui {
class table;
}

class table : public QMainWindow
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = nullptr);
    ~table();
private slots:
    void on_btn_edit_clicked();
private:
    Ui::table *ui;
    edit *editpage;
};

#endif // TABLE_H
