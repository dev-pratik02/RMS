#include "table.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // Use relative path: database file is in the same folder as .exe
    // db.setDatabaseName("rms_app.db");
    db.setDatabaseName("/Users/pratik/Programming/RMS/RMS_qt/RmsApp.db");


    qDebug() << "Trying to open database file at:" << db.databaseName();

    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
        return -1;
    }

    qDebug() << "Database connected!";
    table w;
    w.show();
    return a.exec();
}
