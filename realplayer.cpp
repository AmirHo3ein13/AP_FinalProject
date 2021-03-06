#include "realplayer.h"
#include "player.h"
#include "QGraphicsScene"
#include "socketthread.h"
#include <QFile>
#include <sstream>
#include <cstring>
#include <QTimer>

using namespace std;

//real player has 5 player,,,

RealPlayer::RealPlayer(SocketThread *thread, QGraphicsScene *s, int a, QString nameOfTeam)
{

    //let the player select his/her team
    QFile file(":/Formatation/format.txt");
    file.open(QIODevice::ReadOnly);
    QString str = file.readLine();
    string st = str.toStdString();
    stringstream ss(st);

    if(a == 1)
        ss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5;
    else
        ss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5;



    p[1] = new Player(x1, y1, thread, a); p[1]->playerNum = 1; p[1]->setPixmap(QPixmap(":/Images/" + nameOfTeam));
    p[2] = new Player(x2, y2, thread, a); p[2]->playerNum = 2; p[2]->setPixmap(QPixmap(":/Images/" + nameOfTeam));
    p[3] = new Player(x3, y3, thread, a); p[3]->playerNum = 3; p[3]->setPixmap(QPixmap(":/Images/" + nameOfTeam));
    p[4] = new Player(x4, y4, thread, a); p[4]->playerNum = 4; p[4]->setPixmap(QPixmap(":/Images/" + nameOfTeam));
    p[5] = new Player(x5, y5, thread, a), p[5]->playerNum = 5; p[5]->setPixmap(QPixmap(":/Images/" + nameOfTeam));

    s->addItem(p[1]);
    s->addItem(p[2]);
    s->addItem(p[3]);
    s->addItem(p[4]);
    s->addItem(p[5]);
    rePos();

}

void RealPlayer::change(bool b)
{
    for(int i = 1; i < 6; i++)
        p[i]->changable = b;
}

//line
void RealPlayer::movePlayer(int a, double b, double c)
{
    p[a]->movePlayer(b, c);
}

//move
void RealPlayer::drawLine(int a, double b, double c)
{
    p[a]->drawLine(b, c);
}

void RealPlayer::rePos()
{
    for(int i = 1; i < 6; i++) {
            p[i]->anForMovingX->stop();
            p[i]->anForMovingY->stop();
            p[i]->animation->stop();
             p[i]->rePositioning();

    }
}
