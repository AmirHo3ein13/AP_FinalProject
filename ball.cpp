#include "ball.h"

Ball::Ball(double cX, double cY, QObject *parent) : QObject(parent), Circle(cX, cY), animation(new QPropertyAnimation(this))// change the circle r, x, y too appropriate things
{
    setPixmap(QPixmap(":/Images/ball.png"));
    setPos(cX - 15, cY - 15);
    r = 15;
    animation->setPropertyName("movePlayers");
    animation->setTargetObject(this);
}

//this is for moving circle and checking collisions of circle
void Ball::setMovingBall(int)
{
    //add some collision check and ...
}

