#include "game.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

Game::Game()
{
    qDebug() << "game constructed";
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QImage(":/Images/fSoccer.jpg"));
    QGraphicsView *v = new QGraphicsView(scene);
    v->setFixedSize(1810, 1018);
    scene->setSceneRect(0, 0, 1800, 1000);
    v->show();
}

