#include "mainwindow.h"
#include "login_page.h"
#include <QApplication>

MainWindow *g_mainWindow = nullptr;
login_page *loginPage =nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    g_mainWindow = new MainWindow();

    loginPage = new login_page();
    loginPage->show();
    return a.exec();
}
