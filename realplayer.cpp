#include "realplayer.h"
#include "player.h"
#include "QGraphicsScene"
#include "socketthread.h"

RealPlayer::RealPlayer(SocketThread *thread, QGraphicsScene *s)
{
    Player *p = new Player (500, 500, thread);
    Player *p1 = new Player (400, 300, thread);
    s->addItem(p);
    s->addItem(p1);

}

