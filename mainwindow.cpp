#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "messagedialog.h"

MainWindow::MainWindow(QTimer *t, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->t = t;
    ui->setupUi(this);
        QPixmap bkgnd(":/Images/bg.png");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
        ui->welcomeL->setStyleSheet("QLabel { background-color : white;}");
        ui->ql->setStyleSheet("QLabel { background-color : white;}");
        ui->ql_2->setStyleSheet("QLabel { background-color : white;}");
        ui->ipL->setStyleSheet("QLabel { background-color : white;}");
        ui->IranRB->setChecked(true);
        ui->germanyRB_2->setChecked(true);

        QMediaPlaylist *playlist = new QMediaPlaylist();
        playlist->addMedia(QUrl("qrc:/sounds/start.mp3"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);

        music = new QMediaPlayer();
        music->setPlaylist(playlist);
        music->setVolume(60);
        music->play();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{

    QString flag1;
    QString flag2;
    if(ui->IranRB->isChecked())
        flag1 = "iran";
    else if(ui->italyRB->isChecked())
        flag1 = "italy";
    else if(ui->germanyRB->isChecked())
        flag1 = "germany";
    else if(ui->brasilRB->isChecked())
        flag1 = "brasil";
    else if(ui->argentinaRB->isChecked())
        flag1 = "argentina";
    else
        flag1 = "spain";

    if(ui->IranRB_2->isChecked())
        flag2 = "iran";
    else if(ui->italyRB_2->isChecked())
        flag2 = "italy";
    else if(ui->germanyRB_2->isChecked())
        flag2 = "germany";
    else if(ui->brasilRB_2->isChecked())
        flag2 = "brasil";
    else if(ui->argentinaRB_2->isChecked())
        flag2 = "argentina";
    else
        flag2 = "spain";

    if(flag1 == flag2)
    {
        messageDialog *m = new messageDialog();
        m->show();
    }
    else
    {
        Game *g = new Game(t, flag1,flag2);
        music->stop();
        this->close();
    }
}

void MainWindow::on_quit_clicked()
{
    this->close();
}
