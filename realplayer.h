#ifndef REALPLAYER_H
#define REALPLAYER_H

#include "socketthread.h"
#include <QPropertyAnimation>
#include "QGraphicsScene"
#include "player.h"

using namespace std;

class RealPlayer
{

public:
        RealPlayer(SocketThread *, QGraphicsScene *, int, QString nameOfTeam);
        void change(bool);
        Player *p[6];

private:
    int score = 0;
    int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;

public:
    bool isMyTurn ;
    void movePlayer(int, double, double);
    void drawLine(int, double, double);
    void rePos();


};

#endif // REALPLAYER_H
