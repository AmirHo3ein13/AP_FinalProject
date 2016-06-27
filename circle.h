#ifndef CIRCLE_H
#define CIRCLE_H


class Circle
{
public:
    Circle(double x, double y);

public:
    double x, y;
    virtual void setMove(int) {};

};

#endif // CIRCLE_H
