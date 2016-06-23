#include "realplayer.h"
#include "player.h"
#include "QGraphicsScene"
#include "socketthread.h"

RealPlayer::RealPlayer(SocketThread *thread, QGraphicsScene *s)
{
    Player *p = new Player (thread);
    s->addItem(p);

}

