#include "player.h"

#include"socketthread.h"
#include "QGraphicsSceneMouseEvent"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <stdlib.h>
#include <cmath>

using namespace std;

Player::Player(SocketThread *thread, QObject *parent) : QObject(parent) , Circle(0, 0) //change the circle r, x, y too
{
    width = 100; height = 110;//this may be changed...
    line = new QGraphicsLineItem(0, 0, 0, 0, this);

    //set Line default things
    p1 = p2 = p3 = line->pen();
    p1.setWidth(10); p2.setWidth(10); p3.setWidth(10);
    p1.setColor(Qt::yellow); p2.setColor("orange"); p3.setColor(Qt::red); //seting line colors

    connect(thread, SIGNAL(movePlayer(double,double)), this, SLOT(movePlayer(double,double)));
    connect(thread, SIGNAL(drawLine(double,double)), this, SLOT(drawLine(double,double)));


    //checking
    setPixmap(QPixmap(":/Images/brasil.png"));
    setPos(900 - 50, 500 - 55);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setAcceptTouchEvents(true);
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setAcceptHoverEvents(true);

}

//this is for moving circle and checking collisions of circle
void Player::setMovePlayers(int)
{
    //add some collision check and ...
}

//when mouse press on player
void Player::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //setting line default color
    line->setPen(p1);
    line->setLine(xC(0), yC(0), xC(0), yC(0));
    this->scene()->addItem(line);
    line->setParentItem(this);
    line->setVisible(true);
}

//when mouse release
void Player::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //send informations to server


    //set line invisible
    line->setVisible(false);
    this->scene()->removeItem(line);
}

//when mouse is moving
void Player::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //send informations to server




    //make line biger by moving mouse...
    line->setLine(xC(0), yC(0), -(event->pos().x() - 2 * xC(0)), -(event->pos().y() - 2 * yC(0)));
    //qDebug() << line->pos().rx() << " " << line->pos().x();
    int tmp = sqrt(event->pos().x() * event->pos().x() + event->pos().y() * event->pos().y());
    changeColorOfLine(tmp);
}

//when server sends movePlayer Singnal
void Player::movePlayer(double, double)
{

}


//when server sends drawLine Signal
void Player::drawLine(double, double)
{

}

double Player::xC(double d) {
    return d + 40;
}

double Player::yC(double d) {
    return d + 44;
}

void Player::changeColorOfLine(int tmp)
{
    if(tmp < 60)
        line->setPen(p1);
    else {
        if(tmp < 90)
            line->setPen(p2);
        else
            line->setPen(p3);
    }
}
