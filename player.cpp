#include "player.h"
#include "ball.h"
#include "socketthread.h"
#include "border.h"
#include "QGraphicsSceneMouseEvent"
#include <QDebug>
#include <stdlib.h>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <stdlib.h>
#include <cmath>

using namespace std;

Player::Player(double cxX, double cyY, SocketThread *thread, QObject *parent) : QObject(parent) , Circle(cxX, cyY), animation(new QPropertyAnimation(this)) //change the circle r, x, y too
{

    r = 35;
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
    setPos(cxX, cyY);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setAcceptTouchEvents(true);
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setAcceptHoverEvents(true);

    animation->setPropertyName("movePlayers");
    animation->setTargetObject(this);

}

//this is for moving circle and checking collisions of circle
//chckin collision between player and ball, player and line
void Player::setMovePlayers(int)
{
    //add some collision check and ...
    this->setPos(this->pos().x() + vX, this->pos().y() + vY);
    vX > 0 ? vX -= fx : vX += fx;
    vY > 0 ? vY -= fy : vY += fy;
    if(abs(vX) < .2 && abs(vY) < .2) {
        animation->stop();
        return;
    }

    QList<QGraphicsItem *> l = this->collidingItems();
    for(int i = 0; i < l.size(); i++) {
        if(Player *c = dynamic_cast<Player *> (l[i])) {
            double thisCx = xC(this->pos().x()), thisCy = yC(this->pos().y()), otherCx = c->xC(c->pos().x()), otherCy = c->yC(c->pos().y());
            thisCy *= -1; otherCy *= -1;
            if(thisCx - otherCx == 0) {
                double tmp = this->vY;
                this->vY = c->vY;
                c->vY = tmp;
            }
            else {
                double mCenters = (thisCy - otherCy) / (thisCx - otherCx);
                double mCNorm = -1. / mCenters;
                double picOfVxOnMC = coss(mCenters) * vX, picOfVxOnMCN = coss(mCNorm) * vX, picOfVyOnMC = sinn(mCenters) * vY * -1, picOfVyOnMCN = sinn(mCNorm) * vY * -1;
                double sPicOfVxONMC = coss(mCenters) * c->vX, sPicofVxOnMCN = coss(mCNorm) * c->vX, sPicOfVyOnMC = sinn(mCenters) * c->vY * -1, sPicOfVyOnMCN = sinn(mCNorm) * c->vY * -1;
                if(mCenters < 0) {
                    picOfVxOnMC *= -1;
                    sPicOfVxONMC *= -1;
                }
                else {
                    picOfVxOnMCN *= -1;
                    sPicofVxOnMCN *= -1;
                }
                double fOnMC = picOfVxOnMC + picOfVyOnMC, fOnMCN = picOfVxOnMCN + picOfVyOnMCN, sOnMC = sPicOfVxONMC + sPicOfVyOnMC, sOnMCN = sPicofVxOnMCN + sPicOfVyOnMCN;
                double tmp = fOnMC;
                fOnMC = sOnMC;
                sOnMC = tmp;
                if(mCenters < 0) {
                    double fVx1 = fOnMCN * coss(mCNorm), fVx2 = fOnMC * coss(mCenters) * -1, fVy1 = fOnMCN * sinn(mCNorm) * -1, fVy2 = fOnMC * sinn(mCenters) * -1;
                    this->vX = fVx1 + fVx2; this->vY = fVy1 + fVy2;
                    double sVx1 = sOnMCN * coss(mCNorm), sVx2 = sOnMC * coss(mCenters) * -1, sVy1 = sOnMCN * sinn(mCNorm) * -1, sVy2 = sOnMC * sinn(mCenters) * -1;
                    c->vX = sVx1 + sVx2; c->vY = sVy1 + sVy2;
                }
                else {
                   double fVx1 = fOnMCN * coss(mCNorm) * -1, fVx2 = fOnMC * coss(mCenters), fVy1 = fOnMCN * sinn(mCNorm) * -1, fVy2 = fOnMC * sinn(mCenters) * -1;
                   this->vX = fVx1 + fVx2; this->vY = fVy1 + fVy2;
                   double sVx1 = sOnMCN * coss(mCNorm) * -1, sVx2 = sOnMC * coss(mCenters), sVy1 = sOnMCN * sinn(mCNorm) * -1, sVy2 = sOnMC * sinn(mCenters) * -1;
                   c->vX = sVx1 + sVx2; c->vY = sVy1 + sVy2;
                }
                qDebug() << "got here";
                this->setPos(this->pos().x() + 2 * this->vX, this->pos().y() + 2 * this->vY);
                c->setPos(c->pos().x() + 2 * c->vX, c->pos().y() + 2 * c->vY);
                this->startAnimaion();
                c->animation->start();
                c->startAnimaion();
            }
        }
        else if(Border *b = dynamic_cast<Border *> (l[i])) {
            if(b->x1 == b->x2) {
                this->vX *= -.8;
                this->setX(this->pos().x() + this->vX);

         }
            else if(b->y1 == b->y2) {
                this->vY *= -.8;
                if(this->pos().y() < 6)
                    this->setY(6);
                if(this->pos().y() + this->r * 2 > 674)
                    this->setY(this->pos().y()- this->r * 2);
                this->setY(this->pos().y() + this->vY);
            }

        }
        else if(Ball *c = dynamic_cast<Ball *> (l[i])) {

            double thisCx = xC(this->pos().x()), thisCy = yC(this->pos().y()), otherCx = c->xC(c->pos().x()), otherCy = c->yC(c->pos().y());
            thisCy *= -1; otherCy *= -1;
            if(thisCx - otherCx == 0) {
                double tmp = this->vY;
                this->vY = c->vY;
                c->vY = tmp;
            }
            else {//collinding ball...
                double mCenters = (thisCy - otherCy) / (thisCx - otherCx);
                double mCNorm = -1. / mCenters;
                double picOfVxOnMC = coss(mCenters) * vX, picOfVxOnMCN = coss(mCNorm) * vX, picOfVyOnMC = sinn(mCenters) * vY * -1, picOfVyOnMCN = sinn(mCNorm) * vY * -1;
                double sPicOfVxONMC = coss(mCenters) * c->vX, sPicofVxOnMCN = coss(mCNorm) * c->vX, sPicOfVyOnMC = sinn(mCenters) * c->vY * -1, sPicOfVyOnMCN = sinn(mCNorm) * c->vY * -1;
                if(mCenters < 0) {
                    picOfVxOnMC *= -1;
                    sPicOfVxONMC *= -1;
                }
                else {
                    picOfVxOnMCN *= -1;
                    sPicofVxOnMCN *= -1;
                }
                double fOnMC = picOfVxOnMC + picOfVyOnMC, fOnMCN = picOfVxOnMCN + picOfVyOnMCN, sOnMC = sPicOfVxONMC + sPicOfVyOnMC, sOnMCN = sPicofVxOnMCN + sPicOfVyOnMCN;
                double tmp = fOnMC;
                fOnMC = sOnMC * 1.4;
                sOnMC = tmp * 1.2;
                if(mCenters < 0) {
                    double fVx1 = fOnMCN * coss(mCNorm), fVx2 = fOnMC * coss(mCenters) * -1, fVy1 = fOnMCN * sinn(mCNorm) * -1, fVy2 = fOnMC * sinn(mCenters) * -1;
                    this->vX = fVx1 + fVx2; this->vY = fVy1 + fVy2;
                    double sVx1 = sOnMCN * coss(mCNorm), sVx2 = sOnMC * coss(mCenters) * -1, sVy1 = sOnMCN * sinn(mCNorm) * -1, sVy2 = sOnMC * sinn(mCenters) * -1;
                    c->vX = sVx1 + sVx2; c->vY = sVy1 + sVy2;
                }
                else {
                   double fVx1 = fOnMCN * coss(mCNorm) * -1, fVx2 = fOnMC * coss(mCenters), fVy1 = fOnMCN * sinn(mCNorm) * -1, fVy2 = fOnMC * sinn(mCenters) * -1;
                   this->vX = fVx1 + fVx2; this->vY = fVy1 + fVy2;
                   double sVx1 = sOnMCN * coss(mCNorm) * -1, sVx2 = sOnMC * coss(mCenters), sVy1 = sOnMCN * sinn(mCNorm) * -1, sVy2 = sOnMC * sinn(mCenters) * -1;
                   c->vX = sVx1 + sVx2; c->vY = sVy1 + sVy2;
                }
                qDebug() << "got here";
                this->setPos(this->pos().x() + 2 * this->vX, this->pos().y() + 2 * this->vY);
                c->setPos(c->pos().x() + 2 * c->vX, c->pos().y() + 2 * c->vY);
                this->startAnimaion();
                c->animation->start();
                c->startAnimaion();
            }
        }
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

//detect collisions
bool Player::collidesWithItem(QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    if(Ball *b = dynamic_cast<Ball *> (other)) {
        double tX = this->Circle::x, tY = this->Circle::y, oX = b->Circle::x, oY = b->Circle::y;
        double tmp = sqrt((tX - oX) * (tX - oX) + (tY - oY) * (tY - oY));
        if(tmp <= this->r + b->r)
            return true;
        return false;
    }
    else if (Player *b = dynamic_cast<Player *> (other)) {
        double tX = this->Circle::x, tY = this->Circle::y, oX = b->Circle::x, oY = b->Circle::y;
        double tmp = sqrt((tX - oX) * (tX - oX) + (tY - oY) * (tY - oY));
        if(tmp <= this->r + b->r)
            return true;
        return false;
    }
    else if(Border *b = dynamic_cast<Border *> (other)) {
        if(b->x1 == b->x2) {
            if(abs(this->Circle::x - b->x1) <= this->r)
                return true;
            return false;
        }
        else {
            if(abs(this->Circle::y - b->y1) <= this->r)
                return true;
            return false;
        }
    }
    return false;
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
