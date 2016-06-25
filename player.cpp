#include "player.h"

#include"socketthread.h"
#include "QGraphicsSceneMouseEvent"
#include <QDebug>
#include <stdlib.h>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <stdlib.h>
#include <cmath>

using namespace std;

Player::Player(SocketThread *thread, QObject *parent) : QObject(parent) , Circle(0, 0), animation(new QPropertyAnimation(this)) //change the circle r, x, y too
{

    width = 70; height = 77;//this may be changed...
    line = new QGraphicsLineItem(0, 0, 0, 0, this);

    //set Line default things
    p1 = p2 = p3 = line->pen();
    p1.setWidth(10); p2.setWidth(10); p3.setWidth(10);
    p1.setColor(Qt::yellow); p2.setColor("orange"); p3.setColor(Qt::red); //seting line colors

    //manipulating thread signals
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

    animation->setPropertyName("movePlayers");
    animation->setTargetObject(this);

}

//this is for moving circle and checking collisions of circle
void Player::setMovePlayers(int)
{
    //add some collision check and ...
    this->setPos(this->pos().x() + vX, this->pos().y() + vY);
    vX > 0 ? vX -= fx : vX += fx;
    vY > 0 ? vY -= fy : vY += fy;
    if(abs(vX) < .2) {
        animation->stop();
        return;
    }

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

    //settin speed
    vX = -(event->pos().x() - this->xC(0)) / 4; // /2 is experiential
    vY = -(event->pos().y() - this->yC(0)) / 4;
    double max = sqrt(vX * vX + vY * vY);
    if(max > 19) {
        vX = 19 * vX / max;
        vY = 19 * vY / max;
    }
    startAnimaion();
}

//when mouse is moving
void Player::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //send informations to server




    //make line biger by moving mouse... we may add triangle
    int tmp = sqrt(event->pos().x() * event->pos().x() + event->pos().y() * event->pos().y());
    if(tmp > 100) {
       double xx = -(event->pos().x() - 2 * xC(0)),yy = -(event->pos().y() - 2 * yC(0));
       xx = xC(0) - ((xC(0) - xx) * 100. / tmp);
       yy = yC(0) - ((yC(0) - yy) * 100. / tmp);
       line->setLine(xC(0), yC(0), xx, yy);
    }
    else {
        line->setLine(xC(0), yC(0), -(event->pos().x() - 2 * xC(0)), -(event->pos().y() - 2 * yC(0)));
    }
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

//returns actual center
double Player::xC(double d) {
    return d + 35;
}

double Player::yC(double d) {
    return d + 38.5;
}

//this func will change the color of Line
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

//this is for starting animation
void Player::startAnimaion()
{
    //function for starting animation of Player
    double tmp = sqrt(vX * vX + vY * vY);
    fx = abs(vX) / (tmp * 6), fy = abs(vY) / (tmp * 6);
    animation->pause();
    animation->setStartValue(vX);
    animation->setEndValue(0);
    animation->setDuration(2000000);
    animation->start();
}
