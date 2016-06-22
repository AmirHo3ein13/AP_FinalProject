#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "circle.h"s

class Player : public QObject , public QGraphicsPixmapItem , public Circle
{
    Q_OBJECT
      Q_PROPERTY(int movePlayer READ movePlayer WRITE setMovePlayer)
public:
    explicit Player(QObject *parent = 0);
    int movePlayer(){};
    void setMovePlayer(int);

    //mouse events
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);

signals:

public slots:
};

#endif // PLAYER_H
