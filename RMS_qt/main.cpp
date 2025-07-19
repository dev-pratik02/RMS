#include "mainwindow.h"
#include "login_page.h"
#include <QApplication>
#include "databasemanager.h"
MainWindow *g_mainWindow = nullptr;
login_page *loginPage =nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    g_mainWindow = new MainWindow();

    DatabaseManager::setupDatabase();
    DatabaseManager::getDatabase();
    loginPage = new login_page();
    loginPage->show();
    return a.exec();
}
