#include "databasemanager.h"
#include <QDebug>

QSqlDatabase& DatabaseManager::getDatabase()
{
    static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "qt_sql_default_connection");

    if (!db.isOpen()) {
        db.setDatabaseName("/Users/pratik/Programming/RMS/RMS_qt/RmsApp.db");

        if (!db.open()) {
            qDebug() << "Failed to open DB:" << db.lastError();
        } else {
            qDebug() << "Database opened successfully";
            QSqlQuery pragmaQuery(db);
            pragmaQuery.exec("PRAGMA journal_mode=WAL;");
        }
    }

    return db;
}



