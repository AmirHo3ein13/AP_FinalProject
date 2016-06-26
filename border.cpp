#include "border.h"
#include <QPen>

Border::Border(double x1, double y1, double x2, double y2, QObject *parent) : QObject(parent)
{

    QPen p = this->pen();
    p.setWidth(10);
    this->setPen(p);
    this->x1 = x1; this->x2 = x2; this->y1 = y1; this->y2 = y2;
    setLine(x1, y1, x2, y2);
}

