#ifndef REALPLAYER_H
#define REALPLAYER_H

#include "player.h"
#include "socketthread.h"


class RealPlayer
{
public:
    RealPlayer(SocketThread *, QGraphicsScene *);

private:
    Player *p1, *p2, *p3, *p4, *p5;
    int score = 0;
};

#endif // REALPLAYER_H
