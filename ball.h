#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "circle.h"
#include <QPropertyAnimation>
#include <cmath>

class Ball : public QObject, public QGraphicsPixmapItem, public Circle
{
    Q_OBJECT
    Q_PROPERTY(int movingBall READ movingBall WRITE setMovingBall)

public:
    explicit Ball(double, double, QObject *parent = 0);
    int movingBall(){};
    void setMovingBall(int);
    double r;
    double xC(double){return this->pos().x() + 15;}
    double yC(double){return this->pos().y() + 15;}
    double vX, vY;
    QPropertyAnimation *animation;
    void startAnimaion();

private:
    //sin and cos for collision
    double coss(double a) {
        return sqrt(1. / (a * a + 1));
    }

    double sinn(double a) {
        double tmp = coss(a);
        return sqrt(1 - tmp * tmp);
    }


signals:

public slots:
};

#endif // BALL_H
