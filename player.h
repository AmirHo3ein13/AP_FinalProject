#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "circle.h"s

class Player : public QObject , public QGraphicsPixmapItem , public Circle
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

signals:

public slots:
};

#endif // PLAYER_H
