#ifndef BORDER_H
#define BORDER_H

#include <QObject>
#include <QGraphicsLineItem>

class Border : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit Border(double x1, double x2, double y1, double y2, QObject *parent = 0);
    double x1, x2, y1, y2;

signals:

public slots:
};

#endif // BORDER_H
