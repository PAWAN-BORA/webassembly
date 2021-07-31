#pragma once
#include "uiObject.h"

class UiButton: public UiObject
{
private:
    /* data */
    double width;
    double height; 
public:
    UiButton(double x, double y, double width, double height);
    ~UiButton();
    void onMouseDown(Point* Point) override;
    void onMouseMove(Point* Point) override; 
    void onMouseUp(Point* Point) override;
    void update() override;
    void render(Canvas* cvs) override;
};