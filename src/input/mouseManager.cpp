#include <iostream>
#include "mouseManager.h"
#include <emscripten.h>
#include "../point/point.h"

std::vector<UiObject*> MouseManager::uiObjects;
void MouseManager::initialize() {
    EM_ASM({
        CANVAS_DATA.cvs.addEventListener("mousedown", (event)=>{
            event.preventDefault();
            event.stopPropagation();
            let cvsSize = CANVAS_DATA.cvs.getBoundingClientRect();
            let ratioX = CANVAS_DATA.cvs.width/cvsSize.width;
            let ratioY = CANVAS_DATA.cvs.height/cvsSize.height;
            let x = (event.clientX-cvsSize.left)*ratioX;
            let y = (event.clientY-cvsSize.top)*ratioY;
            console.log(x, y);
            wasmTable.get($0)(x, y);
        });
        CANVAS_DATA.cvs.addEventListener("mousemove", ()=>{
            event.preventDefault();
            event.stopPropagation();
            let cvsSize = CANVAS_DATA.cvs.getBoundingClientRect();
            let ratioX = CANVAS_DATA.cvs.width/cvsSize.width;
            let ratioY = CANVAS_DATA.cvs.height/cvsSize.height;
            let x = (event.clientX-cvsSize.left)*ratioX;
            let y = (event.clientY-cvsSize.top)*ratioY;
            wasmTable.get($1)(x, y);
        });
        CANVAS_DATA.cvs.addEventListener("mouseup", ()=>{
            event.preventDefault();
            event.stopPropagation();
            let cvsSize = CANVAS_DATA.cvs.getBoundingClientRect();
            let ratioX = CANVAS_DATA.cvs.width/cvsSize.width;
            let ratioY = CANVAS_DATA.cvs.height/cvsSize.height;
            let x = (event.clientX-cvsSize.left)*ratioX;
            let y = (event.clientY-cvsSize.top)*ratioY;
            wasmTable.get($2)(x, y);
        });
        
    }, MouseManager::mouseDown, MouseManager::mouseMove, MouseManager::mouseUp);

}
void MouseManager::addObject(UiObject* uiObject) {
   uiObjects.push_back(uiObject);
}
void MouseManager::removeObject(UiObject* uiObject) {

}
void MouseManager::mouseDown(const double x, const double y) {
    // std::cout << "mouse down" << std::endl;
    // std::cout << x << "<->" << y <<std::endl;
    Point point = Point(x, y);
    for(UiObject* uiObject: uiObjects) {
        uiObject->onMouseDown(&point);
    }
}
void MouseManager::mouseMove(const double x, const double y) {
    // std::cout << "mouse move" << std::endl;
    // std::cout << x << y <<std::endl;
    Point point = Point(x, y);
    for(UiObject* uiObject: uiObjects) {
        uiObject->onMouseMove(&point);
    }
}
void MouseManager::mouseUp(const double x, const double y) {
    // std::cout << "mouse up" << std::endl;
    // std::cout << x << "<->" << y <<std::endl;
    Point point = Point(x, y);
    for(UiObject* uiObject: uiObjects) {
        uiObject->onMouseUp(&point);
    }
}