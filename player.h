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
    Q_PROPERTY(int changeX READ changeX WRITE setChangeX)
    Q_PROPERTY(int changeY READ changeY WRITE setChangeY)
public:
    explicit Player(double, double, SocketThread *thread, int number, QObject *parent = 0);

    //animation for moving players
    int changeX(){return this->pos().x();};
    void setChangeX(int);
    int changeY(){return this->pos().y();};
    void setChangeY(int);

    int movePlayers(){return 0;};
    void setMovePlayers(int);
    int playerNum;
    //mouse events
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
    bool collidesWithItem(QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    double r;
    double xC(double);
    double yC(double);
    double fx, fy, vX, vY;
    void startAnimaion();
        QPropertyAnimation *animation, *anForMovingX, *anForMovingY;

private:
    int width, height;
    QGraphicsLineItem *line;
    QPen p1, p2, p3;
    void changeColorOfLine(int tmp);
    int finalDesX, finalDexY, number;

    //sin and cos for collision
    double coss(double a) {
        return sqrt(1. / (a * a + 1));
    }

    double sinn(double a) {
        double tmp = coss(a);
        return sqrt(1 - tmp * tmp);
    }
    void rePositioning();


signals:

private slots:
    void movePlayer(double, double);
    void drawLine(double, double);

public slots:
};

#endif // PLAYER_H
