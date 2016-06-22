#include "player.h"


Player::Player(QObject *parent) : QObject(parent) , Circle(0, 0, 0) //change the circle r, x, y too
{

}

//this is for moving circle and checking collisions of circle
void Player::setMovePlayer(int)
{
    //add some collision check and ...
}

//when mouse press on player
void Player::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

//when mouse release
void Player::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

//when mouse is moving
void Player::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}
