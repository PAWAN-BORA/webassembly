#pragma once
#include <vector>
#include "../ui/uiObject.h"
class MouseManager
{
private:
    /* data */
    static std::vector<UiObject*> uiObjects;
public:
    MouseManager(/* args */) = delete;
    ~MouseManager() ;
    static void initialize();
    static void addObject(UiObject* uiObject);
    static void removeObject(UiObject* uiObject);
    static void mouseDown(const double x, const double y);
    static void mouseMove(const double x, const double y);
    static void mouseUp(const double x, const double y);
};


