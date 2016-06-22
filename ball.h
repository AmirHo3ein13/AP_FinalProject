#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "circle.h"
#include <QPropertyAnimation>

class Ball : public QObject, public QGraphicsPixmapItem, public Circle
{
    Q_OBJECT
    Q_PROPERTY(int movingBall READ movingBall WRITE setMovingBall)

public:
    explicit Ball(QObject *parent = 0);
    int movingBall(){};
    void setMovingBall(int);

signals:

public slots:
};

#endif // BALL_H
