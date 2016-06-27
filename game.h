#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include <realplayer.h>
#include <ball.h>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>

class Game : public QObject
{
    Q_OBJECT
   public:
       explicit Game(QString,QString);
   private:
       QTimer *timer;
       RealPlayer *p1, *p2;
       QGraphicsScene *scene;
       Ball *ball;
       int num;
       SocketThread *t;

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
