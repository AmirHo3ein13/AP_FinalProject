#include "realplayer.h"
#include "player.h"
#include "QGraphicsScene"
#include "socketthread.h"
#include <QFile>
#include <sstream>
#include <cstring>

using namespace std;

RealPlayer::RealPlayer(SocketThread *thread, QGraphicsScene *s, int a, QString nameOfTeam)
{
    //let the player select his team
    QFile file(":/Formatation/format.txt");
    file.open(QIODevice::ReadOnly);
    QString str = file.readLine();
    string st = str.toStdString();
    stringstream ss(st);
    int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
    if(a == 1)
        ss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5;
    else
        ss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5;



    p1 = new Player(x1, y1, thread, a); p1->playerNum = 1; p1->setPixmap(QPixmap(":/Images/" + nameOfTeam));
    p2 = new Player(x2, y2, thread, a); p2->playerNum = 2; p2->setPixmap(QPixmap(":/Images/" + nameOfTeam));
    p3 = new Player(x3, y3, thread, a); p3->playerNum = 3; p3->setPixmap(QPixmap(":/Images/" + nameOfTeam));
    p4 = new Player(x4, y4, thread, a); p4->playerNum = 4; p4->setPixmap(QPixmap(":/Images/" + nameOfTeam));
    p5 = new Player(x5, y5, thread, a), p5->playerNum = 5; p5->setPixmap(QPixmap(":/Images/" + nameOfTeam));

    s->addItem(p1);
    s->addItem(p2);
    s->addItem(p3);
    s->addItem(p4);
    s->addItem(p5);

}

