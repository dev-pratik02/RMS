#ifndef CATEGORY_H
#define CATEGORY_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class category;
}

class category : public QDialog
{
    Q_OBJECT

public:
    explicit category(QWidget *parent = nullptr);
    ~category();
    void loadCategories();

private slots:
    void on_btn_addcategory_clicked();

private:
    Ui::category *ui;

private:
    void handleEditCategory(QString name, QString id, QString itemCount, QString description);
    void handleDeleteCategory(QString id);

};

#endif // CATEGORY_H
