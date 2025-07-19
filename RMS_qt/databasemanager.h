#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QtSql>

class DatabaseManager
{
public:
    static QSqlDatabase& getDatabase();
    static QString writableDbPath;
    static void setupDatabase();
};

#endif // DATABASEMANAGER_H
