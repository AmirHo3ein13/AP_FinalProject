#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include <realplayer.h>
#include <ball.h>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>

class Game
{
public:
    Game();
private:
    QTimer *timer;
    RealPlayer *p1, *p2;
    QGraphicsScene *scene;
    Ball *ball;


    //QTcpSocket with thread...
    //add appropriate lines...
    //some labels for scoring and ...

};

#endif // GAME_H
