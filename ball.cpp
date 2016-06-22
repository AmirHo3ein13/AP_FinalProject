#include "ball.h"

Ball::Ball(QObject *parent) : QObject(parent), Circle(0, 0, 0)// change the circle r, x, y too appropriate things
{

}

//this is for moving circle and checking collisions of circle
void Ball::setMovingBall(int)
{
    //add some collision check and ...
}

