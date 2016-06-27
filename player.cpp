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
#include <QMediaPlayer>
#include "realplayer.h"
#include <QPropertyAnimation>rr

using namespace std;


Player::Player(double cxX, double cyY, SocketThread *thread, int number) : Circle(cxX, cyY), animation(new QPropertyAnimation(this)) //change the circle r, x, y too
{

    this->thread = thread;
    this->number = number;
    this->vX = this->vY = 0;
    r = 35;
    width = 70; height = 77;//this may be changed...
    line = new QGraphicsLineItem(0, 0, 0, 0, this);

    //set Line default things
    p1 = p2 = p3 = line->pen();
    p1.setWidth(10); p2.setWidth(10); p3.setWidth(10);
    p1.setColor(Qt::yellow); p2.setColor("orange"); p3.setColor(Qt::red); //seting line colors
    //manipulating thread signals



    //checking
    if(number == 1)
        setPos(0, 0);
    else
        setPos(1175, 0);
    anForMovingX = new QPropertyAnimation(); anForMovingY = new QPropertyAnimation(this);
    anForMovingX->setPropertyName("changeX"); anForMovingY->setPropertyName("changeY");
    finalDesX = cxX; finalDexY = cyY;
    //rePositioning();
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setAcceptTouchEvents(true);
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setAcceptHoverEvents(true);

    animation->setStartValue(vX);
    animation->setEndValue(.1);
    animation->setPropertyName("movePlayers");
    animation->setTargetObject(this);

}

//this func is for changing coordinates for QPropertyAnimation
void Player::setChangeX(int)
{
    if(this->pos().x() - this->finalDesX > 0) {
        if(abs(this->pos().x() - 5) > this->finalDesX)
            this->setX(this->pos().x() - 5);
        else {
            this->setX(this->pos().x() - abs(this->pos().x() - this->finalDesX));
            this->anForMovingX->stop();
        }
    }
    else {
        if(abs(this->pos().x() + 5) < this->finalDesX)
            this->setX(this->pos().x() + 5);
        else {
            this->setX(this->pos().x() + abs(this->pos().x() - this->finalDesX));
            this->anForMovingX->stop();
        }
    }
}

//this func changes the coordinate for QPropertyAnimation
void Player::setChangeY(int)
{
    if(this->pos().y() - this->finalDexY > 0) {
        if(abs(this->pos().y() - 5) > finalDexY)
            this->setY(this->pos().y() - 5);
        else {
            this->setY(this->pos().y() - abs(this->pos().y() - this->finalDexY));
            this->anForMovingY->stop();
        }
    }
    else {
        if(abs(this->pos().y() + 5) < finalDexY)
            this->setY(this->pos().y() + 5);
        else {
            this->setY(this->pos().y() + abs(this->pos().y() - this->finalDexY));
            this->anForMovingY->stop();
        }
    }
}

//this is for moving circle and checking collisions of circle
//chckin collision between player and ball, player and line
void Player::setMove(int)
{
    //add some collision check and ...
    this->setPos(this->pos().x() + vX, this->pos().y() + vY);

    if(this->pos().x() <= 109 && (this->pos().y() <= 226 || this->pos().y() - this->r * 2 >= 458)) {
        this->vX *= -.8;
        this->setX(111);
    }
    if(this->pos().x() + this->r * 2 >= 1175 && (this->pos().y() <= 226 || this->pos().y() - this->r * 2 >= 458)) {
        this->vX *= -.8;
        this->setX(1173 - this->r * 2);
    }
    if(this->pos().y() <= 10) {
        this->setY(11);
        this->vY *= -.8;
    }
    if(this->pos().y() + this->r * 2 >= 674) {
        this->setY(674 - this->r * 2);
        this->vY *= -.8;
    }
    if(this->pos().x() < 109 && (this->pos().y() > 226 && this->pos().y() - this->r * 2 < 458)) {
        if(this->pos().x() <= 35) {
            this->vX *= -.8;
            this->setX(36);
        }
        if(this->pos().y() <= 234) {
            this->vY *= -.8;
            this->setY(235);
        }
        if(this->pos().y() + this->r * 2 >= 458) {
            this->vY *= -.8;
            this->setY(457 - this->r * 2);
        }
    }

    if(this->pos().x() + this->r * 2 > 1175 && (this->pos().y() > 230 && this->pos().y() - this->r * 2 < 458)) {
        if(this->pos().x() + this->r * 2 >= 1250) {
            this->vX *= -.8;
            this->setX(1249 - this->r * 2);
        }
        if(this->pos().y() <= 234) {
            this->vY *= -.8;
            this->setY(235);
        }
        if(this->pos().y() + this->r * 2 >= 458) {
            this->vY *= -.8;
            this->setY(457 - this->r * 2);
        }
    }


    vX > 0 ? vX -= fx : vX += fx;
    vY > 0 ? vY -= fy : vY += fy;
    if(abs(vX) < .2 && abs(vY) < .2) {

        animation->stop();
        return;
    }

    QList<QGraphicsItem *> l = this->collidingItems();
    for(int i = 0; i < l.size(); i++) {
        if(Player *c = dynamic_cast<Player *> (l[i])) {

            //adding sound of collision between players...
            QMediaPlayer *shot = new QMediaPlayer();
            shot->setMedia(QUrl("qrc:/sounds/p2p.flac"));
            shot->setVolume(110);
            shot->play();

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
                this->startAnimaion();
                c->startAnimaion();
            }
        }

        else if(Ball *c = dynamic_cast<Ball *> (l[i])) {

            //adding sound of collision between player and ball...
            QMediaPlayer *shot = new QMediaPlayer();
            shot->setMedia(QUrl("qrc:/sounds/p2p.flac"));
            shot->setVolume(110);
            shot->play();

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
                this->startAnimaion();
                c->startAnimaion();
            }
        }
    }
}

//when mouse press on player
void Player::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(changable) {
        //setting line default color
        line->setPen(p1);
        line->setLine(xC(0), yC(0), xC(0), yC(0));
        this->scene()->addItem(line);
        line->setParentItem(this);
        line->setVisible(true);
    }
}

//when mouse release
void Player::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(changable) {
        //send informations to server



        //set line invisible
        line->setVisible(false);
        this->scene()->removeItem(line);

        //settin speed
        vX = -(event->pos().x() - this->xC(0)) / 3; // /7 is experiential
        vY = -(event->pos().y() - this->yC(0)) / 3;
        double max = sqrt(vX * vX + vY * vY);
        if(max > 12) {
            vX = 12 * vX / max;
            vY = 12 * vY / max;
        }
        *changeTurn = 9;
        startAnimaion();
    }
}

//when mouse is moving
void Player::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(changable) {
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

        //send informations to server
        QString st = "1 " + QString::number(this->playerNum) + " " + QString::number(-(event->pos().x() - 2 * xC(0))) + " " + QString::number(-(event->pos().y() - 2 * yC(0))) + " ";
        st.append(QChar(23));
        //thread->sendMess(st);
    }
    else {
        line->setVisible(false);
        this->scene()->removeItem(line);
    }
}

//detect collisions
bool Player::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    if(const Ball *b = dynamic_cast<const Ball *> (other)) {
        double tX = this->pos().x() + 35, tY = this->pos().y() + 35, oX = b->pos().x() + 15, oY = b->pos().y() + 15;
        double tmp = sqrt((tX - oX) * (tX - oX) + (tY - oY) * (tY - oY));
        if(tmp <= 50) {
            return true;
        }
        return false;
    }
    else if (const Player *b = dynamic_cast<const Player *> (other)) {
        double tX = this->pos().x(), tY = this->pos().y(), oX = b->pos().x(), oY = b->pos().y();
        double tmp = sqrt((tX - oX) * (tX - oX) + (tY - oY) * (tY - oY));
        if(tmp <= 70)
            return true;
        return false;
    }
    return false;
}

//when server sends movePlayer Singnal
void Player::movePlayer(double, double)
{

}


//when server sends drawLine Signal
void Player::drawLine(double a, double b)
{
    a = abs(a - xC(this->pos().x())); b = abs(b - yC(this->pos().y()));
    int tmp = sqrt(a * a + b * b);

    changeColorOfLine(tmp);
}

//returns actual center
double Player::xC(double d) {
    return d + 35;
}

double Player::yC(double d) {
    return d + 35;
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

//animation of starting...
void Player::rePositioning()
{
    anForMovingX->setDuration(3000); anForMovingY->setDuration(3000);
    anForMovingX->setStartValue(this->pos().x()); anForMovingX->setEndValue(this->finalDesX);
    anForMovingY->setStartValue(this->pos().y()); anForMovingY->setEndValue(this->finalDexY);
    anForMovingX->setTargetObject(this); anForMovingY->setTargetObject(this);
    anForMovingX->start(); anForMovingY->start();
}

//this is for starting animation
void Player::startAnimaion()
{
    //function for starting animation of Player
    double tmp = sqrt(vX * vX + vY * vY);
    fx = abs(vX) / (tmp * 10), fy = abs(vY) / (tmp * 10);
    animation->pause();
    animation->setStartValue(vX);
    animation->setEndValue(0);
    animation->setDuration(10000);
    animation->start();

}
