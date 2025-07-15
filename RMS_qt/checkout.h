#ifndef CHECKOUT_H
#define CHECKOUT_H
#include <QDialog>
#include <QList>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QGridLayout>
#include <QFrame>
#include <QRegularExpression>
#include <QtSql>
namespace Ui {
class checkout;
}

class checkout : public QDialog
{
    Q_OBJECT

public:
    explicit checkout(const QString &orderId, const QString &table, const QString &time, const QString &status,
                      const QList<QList<QString>> &items, QWidget *parent = nullptr);
    ~checkout();

private:
    Ui::checkout *ui;
    QSqlDatabase db;
};

#endif // CHECKOUT_H
