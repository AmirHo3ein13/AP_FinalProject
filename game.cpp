#include "game.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

Game::Game()
{
    qDebug() << "game constructed";
    scene = new QGraphicsScene();
    QGraphicsView *v = new QGraphicsView(scene);
    v->setFixedSize(1800, 1000);
    scene->setSceneRect(0, 0, 1800, 1000);
    scene->setBackgroundBrush(QBrush(QImage("/home/mehran/Downloads/rsz_sockerfield.jpg")));
    v->show();
}

