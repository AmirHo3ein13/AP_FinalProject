#include "game.h"
#include "realplayer.h"
#include "socketthread.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include "ball.h"
Game::Game()
{
    qDebug() << "game constructed";
   SocketThread *t = new SocketThread();
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QImage(":/Images/fSoccer.jpg"));
    QGraphicsView *v = new QGraphicsView(scene);
    v->setFixedSize(1770, 1015);
    scene->setSceneRect(0, 0, 1758, 1000);
    Ball *b = new Ball();
    scene->addItem(b);
    RealPlayer p(t, scene);
    v->show();
}

