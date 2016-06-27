#include "mainwindow.h"
#include <QApplication>
#include "game.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer *t = new QTimer(&a);
    MainWindow *mainwindow = new MainWindow(t);
    mainwindow->show();

    return a.exec();
}
