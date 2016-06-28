#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "circle.h"
#include <QPropertyAnimation>
#include <cmath>
#include <QLabel>
#include "realplayer.h"

class Ball : public QObject, public QGraphicsPixmapItem, public Circle
{
    Q_OBJECT
    Q_PROPERTY(int movingBall READ movingBall WRITE setMoving)
    Q_PROPERTY(int changeX READ changeX WRITE setChangeX)
    Q_PROPERTY(int changeY READ changeY WRITE setChangeY)

public:
    explicit Ball(RealPlayer *p1, RealPlayer *p2,QLabel *l1, QLabel *l2, double, double, QObject *parent = 0);
    int movingBall(){};

    SocketThread *thread;

    void setMoving(int);
    double r;
    double xC(double a){return a + 15;}
    double yC(double a){return a + 15;}
    double vX, vY, fX, fY;
    QPropertyAnimation *animation, *anForMovingX, *anForMovingY;
    void startAnimaion();
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    void rePositioning();


private:
    int changeX(){return this->pos().x();};
    void setChangeX(int);
    int changeY(){return this->pos().y();};
    void setChangeY(int);

    //sin and cos for collision
    double coss(double a) {
        return sqrt(1. / (a * a + 1));
    }

    double sinn(double a) {
        double tmp = coss(a);
        return sqrt(1 - tmp * tmp);
    }

    QLabel *l1, *l2;
    RealPlayer *p1, *p2;


signals:

public slots:
};

#endif // BALL_H
