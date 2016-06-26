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
    Player *p[5];
    int score = 0;

public:
    void movePlayer(int, double, double);
    void drawLine(int, double, double);
};

#endif // REALPLAYER_H
