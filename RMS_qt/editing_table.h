#ifndef EDITING_TABLE_H
#define EDITING_TABLE_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class editing_table;
}

class editing_table : public QDialog
{
    Q_OBJECT

public:
    explicit editing_table(QWidget *parent = nullptr);
    ~editing_table();

    void setData(const QString &table_no, const QString &seats, const QString &location,
                const QString &type, const QString &description);

signals:
    void dataUpdated();

private slots:
    void on_btn_change_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::editing_table *ui;
    QSqlDatabase db;
    QString original_table_no;
};

#endif
