#include "game.h"
#include "realplayer.h"
#include "socketthread.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include "ball.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

Game::Game()
{
    qDebug() << "game constructed";
   SocketThread *t = new SocketThread();
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QImage(":/Images/fSoccer.jpg"));

    //scene adjustment
    QGraphicsView *v = new QGraphicsView(scene);
    v->setFixedSize(1280, 680);
    scene->setSceneRect(0, 0, 1280, 680);

    //creating ball
    Ball *b = new Ball();

    //creating players & goals
    QGraphicsPixmapItem *pm1 = new QGraphicsPixmapItem(),*pm2 = new QGraphicsPixmapItem();
    pm1->setPixmap(QPixmap(":/Images/goal.png"));
    pm2->setPixmap(QPixmap(":/Images/goal.png"));
    pm1->setPos(30,232);
    pm2->setPos(1172,230);
    scene->addItem(b);
    RealPlayer p(t, scene);
    scene->addItem(pm1);
    scene->addItem(pm2);
    v->show();
}

