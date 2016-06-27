#include "ball.h"
#include "player.h"
#include "border.h"
#include <QDebug>
#include <QMediaPlayer>
#include <QLabel>
#include <stdlib.h>
#include <unistd.h>

Ball::Ball(RealPlayer *p1, RealPlayer *p2, QLabel *l1, QLabel *l2, double cX, double cY, QObject *parent) : QObject(parent), Circle(cX, cY), animation(new QPropertyAnimation(this))// change the circle r, x, y too appropriate things
{
    setPos(0, 0);
    this->l1 = l1; this->l2 = l2;
    this->p1 = p1; this->p2 = p2;
    this->vX = 0; this->vY = 0;
    setPixmap(QPixmap(":/Images/ball.png"));
    r = 15;
    animation->setPropertyName("movingBall");
    animation->setTargetObject(this);

    anForMovingX = new QPropertyAnimation(); anForMovingY = new QPropertyAnimation(this);
    anForMovingX->setPropertyName("changeX"); anForMovingY->setPropertyName("changeY");
    rePositioning();
}


//this func is for changing coordinates for QPropertyAnimation
void Ball::setChangeX(int)
{
    if(this->pos().x() - 624.5 > 0) {
        if(abs(this->pos().x() - 5) > 624.5)
            this->setX(this->pos().x() - 5);
        else {
            this->setX(this->pos().x() - abs(this->pos().x() - 624.5));
            this->anForMovingX->stop();
        }
    }
    else {
        if(abs(this->pos().x() + 5) < 624.5)
            this->setX(this->pos().x() + 5);
        else {
            this->setX(this->pos().x() + abs(this->pos().x() - 624.5));
            this->anForMovingX->stop();
        }
    }
}

//this func changes the coordinate for QPropertyAnimation
void Ball::setChangeY(int)
{
    if(this->pos().y() - 325 > 0) {
        if(abs(this->pos().y() - 5) > 325)
            this->setY(this->pos().y() - 5);
        else {
            this->setY(this->pos().y() - abs(this->pos().y() - 325));
            this->anForMovingY->stop();
        }
    }
    else {
        if(abs(this->pos().y() + 5) < 325)
            this->setY(this->pos().y() + 5);
        else {
            this->setY(this->pos().y() + abs(this->pos().y() - 325));
            this->anForMovingY->stop();
        }
    }
}


//this is for moving circle and checking collisions of circle
void Ball::setMoving(int)
{
    //checking for goal,
    if(this->xC(this->pos().x()) > 1177 && this->pos().y() > 228 && this->pos().y() < 453) {
        int num = l1->text().toInt();
        num++;
        l1->setText(QString::number(num));
        this->animation->stop();
        rePositioning();
        p1->rePos();
        p2->rePos();
    }
    if(this->xC(this->pos().x()) <103 && this->pos().y() > 228 && this->pos().y() < 456) {
        int num = l2->text().toInt();
        num++;
        l2->setText(QString::number(num));
        rePositioning();
        this->animation->stop();
        p1->rePos();
        p2->rePos();
    }

    //add some collision check and ...
    this->setPos(this->pos().x() + vX, this->pos().y() + vY);
    vX > 0 ? vX -= fX : vX += fX;
    vY > 0 ? vY -= fY : vY += fY;
    if(abs(vX) < .2 && abs(vY) < .2) {
        animation->stop();
        return;
    }
    QList<QGraphicsItem *> l = this->collidingItems();
    for(int i = 0; i < l.size(); i++) {
        if(Border *b = dynamic_cast<Border *> (l[i])) {

            //addin sounds of ball and border collision...
            QMediaPlayer *shot = new QMediaPlayer();
            shot->setMedia(QUrl("qrc:/sounds/p2p.flac"));
            shot->setVolume(110);
            shot->play();

            if(b->x1 == b->x2) {
                this->vX *= -.8;
                this->setPos(this->pos().x() + 2 * this->vX, this->pos().y() + 2 * this->vY);

//                if(abs(xC(this->pos().x()) - b->x()) < this->r) {
//                    if(xC(this->pos().x()) - b->x() < 0)
//                        this->setX(this->pos().x() - abs(b->x() - this->r));
//                    else if(xC(this->pos().x() - (b->x() + 5) > 0))
//                        this->setX(this->pos().x() + abs(b->x() - this->r));
//                }

         }
            //else if(b->y1 == b->y2) {
            else if(this->pos().y() <= 10 || this->pos().y() + this->r * 2 >= 674) {
                this->vY *= -.6;
                this->setPos(this->pos().x() + 2 * this->vX, this->pos().y() + 2 * this->vY);
                if(this->pos().y() < 10)
                    this->setY(10);
                else if(this->pos().y() > 674 - this->r * 2)
                    this->setY(674);
//                if(this->pos().y() < 6)
//                    this->setY(6);
//                if(this->pos().y() + this->r * 2 > 674)
//                    this->setY(this->pos().y()- this->r * 2);
//                this->setY(this->pos().y() + this->vY);
            }
        }

        //checking collision between player and ball
        if(Player *c = dynamic_cast<Player *> (l[i])) {

            //adding sounds of collision between ball and player...
            QMediaPlayer *shot = new QMediaPlayer();
            shot->setMedia(QUrl("qrc:/sounds/shot.wav"));
            shot->setVolume(110);
            shot->play();

            double thisCx = xC(this->pos().x()), thisCy = yC(this->pos().y()), otherCx = c->xC(c->pos().x()), otherCy = c->yC(c->pos().y());
            //thisCy *= -1; otherCy *= -1;
            if(thisCx - otherCx == 0) {
                double tmp = this->vY;
                this->vY = c->vY;
                c->vY = tmp;
            }
            else {
                //calculating speed of ball and palyer after collision
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
                this->setPos(this->pos().x() + 3 * this->vX, this->pos().y() + 3 * this->vY);
                c->setPos(c->pos().x() + 2 * c->vX, c->pos().y() + 2 * c->vY);
                this->startAnimaion();
                c->startAnimaion();
            }
        }
    }

}

void Ball::startAnimaion()
{
    //function for starting animation of Player
    double tmp = sqrt(vX * vX + vY * vY);
    fX = abs(vX) / (tmp * 9), fY = abs(vY) / (tmp * 9);
    animation->pause();
    animation->setStartValue(vX);
    animation->setEndValue(0);
    animation->setDuration(2000000);
    animation->start();
}


//this item checks if things collide with ball...
bool Ball::collidesWithItem(QGraphicsItem *other, Qt::ItemSelectionMode mode)
{
    
    if (Player *b = dynamic_cast<Player *> (other)) {
        double tX = this->Circle::x, tY = this->Circle::y, oX = b->Circle::x, oY = b->Circle::y;
        double tmp = sqrt((tX - oX) * (tX - oX) + (tY - oY) * (tY - oY));
        if(tmp <= this->r + 3 + b->r)
            return true;
        return false;
    }
    else if(Border *b = dynamic_cast<Border *> (other)) {
        if(b->x1 == b->x2) {
            if(this->pos().x() <= b->x1 + 100)
                return true;
            return false;
        }
        else {
            double yy = this->Circle::y;
            if(abs(yC(this->pos().y()) - b->y1) <= this->r + 2)
                return true;
            return false;
        }
    }
    return false;
}


//animation of starting...
void Ball::rePositioning()
{
    anForMovingX->setDuration(3000); anForMovingY->setDuration(3000);
    anForMovingX->setStartValue(this->pos().x()); anForMovingX->setEndValue(624.5);
    anForMovingY->setStartValue(this->pos().y()); anForMovingY->setEndValue(325);
    anForMovingX->setTargetObject(this); anForMovingY->setTargetObject(this);
    anForMovingX->start(); anForMovingY->start();
}
