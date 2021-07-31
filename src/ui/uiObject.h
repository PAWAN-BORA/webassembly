#pragma once
#include "../point/point.h"
#include "../canvas.h"
class UiObject
{
private:
    /* data */
protected: 
    double x;
    double y;
    UiObject(double x, double y):x(x), y(y){};
    ~UiObject(){};
public:
    virtual void onMouseDown(Point* point) = 0;
    virtual void onMouseMove(Point* point) = 0;
    virtual void onMouseUp(Point* point) = 0;
    virtual void update() = 0;
    virtual void render(Canvas* cvs) = 0;
};


