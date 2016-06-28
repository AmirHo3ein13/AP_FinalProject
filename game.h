#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include <realplayer.h>
#include <ball.h>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QProgressBar>

class Game : public QObject
{
    Q_OBJECT
   public:
       explicit Game(SocketThread *, QTimer *, QString,QString);
       int chan = 0;
       Ball *b;

   private:
       QTimer *timer;
       RealPlayer *p1, *p2;
       QGraphicsScene *scene;
       Ball *ball;
       int num;
       SocketThread *t;
       QProgressBar *bar1, *bar2;
       QLabel *q1, *q2;

   private slots:
       void setTurn();
       void movePlayer(int, int, double, double);
       void drawLine(int, double, double);
       void playerN(int);
       void BallMv(double, double);
       void changeTurn();


       //QTcpSocket with thread...
       //add appropriate lines...
       //some labels for scoring and ...
};

#endif // GAME_H
