#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "circle.h"

class Ball : public QObject, public QGraphicsPixmapItem, public Circle
{
    Q_OBJECT
public:
    explicit Ball(QObject *parent = 0);

signals:

public slots:
};

#endif // BALL_H
