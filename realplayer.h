#ifndef REALPLAYER_H
#define REALPLAYER_H

#include "player.h"
#include "socketthread.h"
#include <QPropertyAnimation>

using namespace std;

class RealPlayer
{
public:
    RealPlayer(SocketThread *, QGraphicsScene *, int, QString nameOfTeam);

private:
    Player *p1, *p2, *p3, *p4, *p5;
    int score = 0;
};

#endif // REALPLAYER_H
