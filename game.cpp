#include "game.h"
#include "realplayer.h"
#include "socketthread.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include "ball.h"
#include "border.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QFile>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QLabel>
#include <QFont>
#include <QProgressBar>


Game::Game(QTimer *timer, QString player1Flag,QString player2Flag)
{

//       t = new SocketThread();
//       connect(t, SIGNAL(drawLine(int,double,double)), this, SLOT(drawLine(int,double,double)));
//       connect(t, SIGNAL(movePlayer(int,double,double)), this, SLOT(movePlayer(int,double,double)));
//       connect(t, SIGNAL(playerN(int)), this, SLOT(playerN(int)));
//       t->start();


       scene = new QGraphicsScene();
       scene->setBackgroundBrush(QImage(":/Images/fSoccer.jpg"));

       //scene adjustment
       QGraphicsView *v = new QGraphicsView(scene);
       v->setFixedSize(1285, 685);
       scene->setSceneRect(0, 0, 1280, 680);


       //creating players & goals
       QGraphicsPixmapItem *pm1 = new QGraphicsPixmapItem(),*pm2 = new QGraphicsPixmapItem();
       QGraphicsPixmapItem *HrD = new QGraphicsPixmapItem(), *HrU = new QGraphicsPixmapItem(),
                   *VrR1 = new QGraphicsPixmapItem(), *VrL1 = new QGraphicsPixmapItem(),
                   *VrR2 = new QGraphicsPixmapItem(), *VrL2 = new QGraphicsPixmapItem();
       pm1->setPixmap(QPixmap(":/Images/goal.png"));
       pm2->setPixmap(QPixmap(":/Images/goal.png"));
       pm1->setPos(30,232);
       pm2->setPos(1172,230);

       HrD->setPixmap(QPixmap(":/Images/hRodD.jpeg"));
           HrU->setPixmap(QPixmap(":/Images/hRodU.jpeg"));
           VrL1->setPixmap(QPixmap(":/Images/vRodL.jpeg"));
           VrL2->setPixmap(QPixmap(":/Images/vRodL.jpeg"));
           VrR1->setPixmap(QPixmap(":/Images/vRodR.jpeg"));
           VrR2->setPixmap(QPixmap(":/Images/vRodR.jpeg"));

       //creating real players...
       p1 = new RealPlayer (t, scene, 1, player1Flag + ".png");
       p2 = new RealPlayer (t, scene, 2, player2Flag + ".png");
       p1->change(true); p2->change(false);
       p1->isMyTurn = true; p2->isMyTurn = false;
       scene->addItem(pm1);
       scene->addItem(pm2);

       //creating ball
       QLabel *q1 = new QLabel, *q2 = new QLabel;
       Ball *b = new Ball(p1, p2, q1, q2, 639.5, 340);
       scene->addItem(b);


       //creating borders
       Border *b1 = new Border(105, 6, 1175, 6), *b2 = new Border(105, 674, 1175, 674), *b3 = new Border(105, 6, 105, 226), *b4 = new Border(105, 458, 105, 674), *b5 = new Border(1175, 6, 1175, 226),
               *b6 = new Border(1175, 455, 1175, 674) , *b7 = new Border(105,226,31,226)
               ,*b8 = new Border(31,226,31,458),*b9 = new Border(31,458,105,458)
               ,*b10 = new Border(1175,226,1250,226),*b11 = new Border(1250,226,1250,455)
               ,*b12 = new Border(1250,455,1175,455);
       b1->setOpacity(0);
       b2->setOpacity(0);
       b3->setOpacity(0);
       b4->setOpacity(0);
       b5->setOpacity(0);
       b6->setOpacity(0);
       b7->setOpacity(0);
       b8->setOpacity(0);
       b9->setOpacity(0);
       b10->setOpacity(0);
       b11->setOpacity(0);
       b12->setOpacity(0);

       HrD->setPos(102,670);
       HrU->setPos(102,4);
       VrL1->setPos(102,6);
       VrL2->setPos(102,448);
       VrR1->setPos(1172,6);
       VrR2->setPos(1172,452);

       scene->addItem(pm1);
       scene->addItem(pm2);
       scene->addItem(HrD);
       scene->addItem(HrU);
       scene->addItem(VrR1);
       scene->addItem(VrR2);
       scene->addItem(VrL1);
       scene->addItem(VrL2);
       scene->addItem(b1);
       scene->addItem(b2);
       scene->addItem(b3);
       scene->addItem(b4);
       scene->addItem(b5);
       scene->addItem(b6);
       scene->addItem(b7);
       scene->addItem(b8);
       scene->addItem(b9);
       scene->addItem(b10);
       scene->addItem(b11);
       scene->addItem(b12);

        // media of game
        QMediaPlaylist *playlist = new QMediaPlaylist();
        playlist->addMedia(QUrl("qrc:/sounds/play.mp3"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);

        QMediaPlayer *music = new QMediaPlayer();
        music->setPlaylist(playlist);
        music->setVolume(50);
        music->play();

        QMediaPlayer *whistle = new QMediaPlayer();
        whistle->setMedia(QUrl("qrc:/sounds/whistle.wav"));
        whistle->setVolume(100);
        whistle->play();

        //adding scores of players
        q2->setGeometry(1182, 0, 100, 50);
        q1->setGeometry(0, 0, 100, 50);
        q1->setText("0");
        QFont f = q1->font();
        f.setBold(true);
        f.setPointSize(25);
        q1->setFont(f);
        q1->setAlignment(Qt::AlignHCenter);
        q2->setFont(f);
        q2->setAlignment(Qt::AlignHCenter);
        q2->setText("0");
        scene->addWidget(q1);
        scene->addWidget(q2);

        bar1 = new QProgressBar;
        bar2 = new QProgressBar;
        bar1->setGeometry(0, 50, 20, 150);
        bar2->setGeometry(1183, 50, 20, 150);
        bar1->setMaximum(100);
        bar2->setMaximum(100);
        bar1->setFixedWidth(100);
        bar2->setFixedHeight(30);
        bar2->setFixedWidth(100);
        bar1->setFixedHeight(30);
        bar1->setValue(0);
        bar2->setValue(0);
        scene->addWidget(bar1);
        scene->addWidget(bar2);
        for(int i = 1; i < 6; i++) {
            p1->p[i]->changeTurn = &chan;
            p2->p[i]->changeTurn = &chan;
        }
        this->timer = timer;
        connect(timer, SIGNAL(timeout()), b, SLOT(raise()));
        connect(timer, SIGNAL(timeout()), this, SLOT(setTurn()));
        timer->start(1000);

        v->show();

}

//changes the turn of players
void Game::setTurn()
{

    chan++;
    if(!(chan % 10)) {
        if(p1->isMyTurn == true) {
            p1->isMyTurn = false;
            p2->isMyTurn = true;
            p1->change(false); p2->change(true);
        }
        else {
            p2->isMyTurn = false;
            p1->isMyTurn = true;
            p2->change(false); p1->change(true);
        }
    }
    if(p1->isMyTurn) {
        bar1->setValue((chan % 10) * 10);
        bar2->setValue(0);
    }
    else if(p2->isMyTurn) {
        bar1->setValue(0);
        bar2->setValue((chan % 10) * 10);
    }
}

void Game::movePlayer(int a, double b, double c)
{
    if(num == 1) {
        p2->movePlayer(a, b, c);
    }
    else
        p1->movePlayer(a, b, c);
}

void Game::drawLine(int a, double b, double c)
{
    if(num == 1)
        p2->drawLine(a, b, c);
    else
        p1->drawLine(a, b, c);
}

void Game::playerN(int a)
{
    num = a;
}




