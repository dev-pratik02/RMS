#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "edit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class table; }
QT_END_NAMESPACE

class table : public QMainWindow
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = nullptr);
    void refreshTableList();
    void updateSeatLabels();
    ~table();

private:
    Ui::table *ui;
    QSqlDatabase db;
    edit *editPage;

    void loadTableList();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_btn_edit_clicked();

};

#endif
