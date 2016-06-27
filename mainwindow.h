#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

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

private:
    QMediaPlayer *music;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
