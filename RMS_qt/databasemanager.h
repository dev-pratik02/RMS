#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QtSql>

class DatabaseManager
{
public:
    static QSqlDatabase& getDatabase();

};

#endif // DATABASEMANAGER_H
