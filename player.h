#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QPen>
#include <QGraphicsLineItem>
#include <QPropertyAnimation>
#include <cmath>
#include "circle.h"
#include "socketthread.h"

class Player : public QObject , public QGraphicsPixmapItem , public Circle
{
    Q_OBJECT
     Q_PROPERTY(int movePlayers READ movePlayers WRITE setMovePlayers)
public:
    explicit Player(double, double, SocketThread *thread, QObject *parent = 0);
    int movePlayers(){return 0;};
    void setMovePlayers(int);

    //mouse events
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
    bool collidesWithItem(QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    double r;

private:
    QPropertyAnimation *animation;
    int width, height;
    double xC(double);
    double yC(double);
    QGraphicsLineItem *line;
    QPen p1, p2, p3;
    void changeColorOfLine(int tmp);
    double fx, fy, vX, vY;
    void startAnimaion();

    //sin and cos for collision
    double coss(double a) {
        return sqrt(1. / (a * a + 1));
    }

    double sinn(double a) {
        double tmp = coss(a);
        return sqrt(1 - tmp * tmp);
    }



signals:

private slots:
    void movePlayer(double, double);
    void drawLine(double, double);

public slots:
};

#endif // PLAYER_H
