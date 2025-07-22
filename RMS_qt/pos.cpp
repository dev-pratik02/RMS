#include "pos.h"
#include "ui_pos.h"
#include "mainwindow.h"
#include "databasemanager.h"

extern MainWindow *g_mainWindow;

pos::pos(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pos)
{
    ui->setupUi(this);
    QSqlDatabase &db = DatabaseManager::getDatabase();



    QStringList table_list;
    int row = 0;

    QSqlQuery query(db);
    if (query.exec("SELECT table_no FROM tables")) {
        while (query.next()) {
            table_list.append(query.value(0).toString());
            row++;
        }
        qDebug() << "No. of tables: " << row;
        ui->pos_table_dropdown->addItems(table_list);
    } else {
        qDebug() << "Failed to fetch tables:" << query.lastError();
    }


}

pos::~pos()
{
    delete ui;
}

void pos::on_btn_place_order_clicked()
{
    QString table_no = ui->pos_table_dropdown->currentText();
    qDebug() << "The table no. is: " << table_no;
    ptraddorder = new POS_AddOrder(table_no, this, g_mainWindow);
    ptraddorder->setAttribute(Qt::WA_DeleteOnClose);
    ptraddorder->show();

}

