#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "socketthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QTimer *t, QWidget *parent = 0);
    QTimer *t;
    ~MainWindow();

private slots:

    void on_start_clicked();

    void on_quit_clicked();

    void nameAccepted();

private:
    QString flag1;
    QMediaPlayer *music;
    Ui::MainWindow *ui;
    SocketThread *thread;
};

#endif // MAINWINDOW_H
