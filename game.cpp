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

Game::Game()
{
    qDebug() << "game constructed";
   SocketThread *t = new SocketThread();
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QImage(":/Images/fSoccer.jpg"));

    //scene adjustment
    QGraphicsView *v = new QGraphicsView(scene);
    v->setFixedSize(1285, 685);
    scene->setSceneRect(0, 0, 1280, 680);

    //creating ball
    Ball *b = new Ball(639.5, 340);

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

    //creating borders
    Border *b1 = new Border(105, 6, 1175, 6), *b2 = new Border(105, 674, 1175, 674), *b3 = new Border(105, 6, 105, 226), *b4 = new Border(105, 458, 105, 674), *b5 = new Border(1175, 6, 1175, 226),
            *b6 = new Border(1175, 455, 1175, 674);
    b1->setOpacity(0);
    b2->setOpacity(0);
    b3->setOpacity(0);
    b4->setOpacity(0);
    b5->setOpacity(0);
    b6->setOpacity(0);


    scene->addItem(b1);
    scene->addItem(b2);
    scene->addItem(b3);
    scene->addItem(b4);
    scene->addItem(b5);
    scene->addItem(b6);

    v->show();
}

