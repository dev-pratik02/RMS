#include "databasemanager.h"
#include <QDebug>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QSqlDatabase>

QString DatabaseManager::writableDbPath;
QSqlDatabase& DatabaseManager::getDatabase()
{

    static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "qt_sql_default_connection");

    if (!db.isOpen()) {
        // db.setDatabaseName(writableDbPath);
        db.setDatabaseName("C:/Users/VICTUS/OneDrive/Desktop/Project/RMS_qt/RmsApp.db");

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

// void DatabaseManager::setupDatabase() {
//     // 1. Determine writable location (AppDataLocation is recommended)
//     QString writablePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

//     // 2. Create the directory if it doesn't exist
//     QDir dir;
//     if (!dir.exists(writablePath)) {
//         dir.mkpath(writablePath);
//     }

//     // 3. Define destination path for writable DB
//     writableDbPath = writablePath + "/RmsApp.db";

//     // 4. Check if DB already exists there; if not, copy from app bundle
//     if (!QFile::exists(writableDbPath)) {
//         QString bundledDbPath = QCoreApplication::applicationDirPath() + "/../Resources/RmsApp.db";

//         if (!QFile::copy(bundledDbPath, writableDbPath)) {
//             qDebug() << "Failed to copy DB from" << bundledDbPath << "to" << writableDbPath;
//         } else {
//             // Optional: make sure copied file is writable
//             QFile::setPermissions(writableDbPath, QFileDevice::ReadOwner | QFileDevice::WriteOwner);
//             qDebug() << "Database copied to writable location:" << writableDbPath;
//         }
//     } else {
//         qDebug() << "Database already exists at writable location:" << writableDbPath;
//     }
// }


