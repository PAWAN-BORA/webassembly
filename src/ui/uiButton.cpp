#include "uiButton.h"
#include <iostream>

UiButton::UiButton(double x, double y, double width, double height):UiObject(x, y), width(width), height(height)
{

}

UiButton::~UiButton()
{
}

void UiButton::onMouseDown(Point* point) {
    std::cout << point->x << " " << point->y << std::endl;
    if()
}

void UiButton::onMouseMove(Point* point) {

}

void UiButton::onMouseUp(Point* point) {
    
}

void UiButton::update() {
    // if(x>0 && x<1366) {
    //     x++;
    // }
}

void UiButton::render(Canvas* cvs) {
    cvs->save();
    cvs->fillStyle("red");
    cvs->fillRect(x, y, width, height);
    cvs->restore();
}

