#include "mainwindow.h"
#include <QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *mainwindow = new MainWindow;
    mainwindow->show();

    return a.exec();
}
