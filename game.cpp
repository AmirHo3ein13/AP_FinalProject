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

       scene->addItem(b);
       RealPlayer p(t, scene);
       scene->addItem(pm1);
       scene->addItem(pm2);

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

       v->show();

}

