#include "databasemanager.h"
#include <QDebug>

QSqlDatabase& DatabaseManager::getDatabase()
{
    static QSqlDatabase db;
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QSQLITE", "qt_sql_default_connection");
        db.setDatabaseName("/Users/pratik/Programming/RMS/RMS_qt/RmsApp.db");
        if (!db.open()) {
            qDebug() << "Failed to open DB";
        } else {
            QSqlQuery pragmaQuery(db);
            pragmaQuery.exec("PRAGMA journal_mode=WAL;");
        }
    } else {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    return db;
}

