#include "mainwindow.h"

#include <QApplication>

MainWindow *g_mainWindow = nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    g_mainWindow = new MainWindow();
    g_mainWindow->show();
    return a.exec();
}
