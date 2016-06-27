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
       explicit Game(QTimer *, QString,QString);
       int chan = 0;
   private:
       QTimer *timer;
       RealPlayer *p1, *p2;
       QGraphicsScene *scene;
       Ball *ball;
       int num;
       SocketThread *t;
       QProgressBar *bar1, *bar2;

   private slots:
       void setTurn();
       void movePlayer(int, double, double);
       void drawLine(int, double, double);
       void playerN(int);

       //QTcpSocket with thread...
       //add appropriate lines...
       //some labels for scoring and ...
};

#endif // GAME_H
