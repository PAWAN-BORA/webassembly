
#include "canvas.h"
// #ifdef __EMSCRIPTEN__
#include <emscripten.h>
// #include <string.h>
#include <iostream>

Canvas::Canvas(const char* canvasId) {

    EM_ASM({
        let id = UTF8ToString($0);
        CANVAS_DATA.cvs= document.getElementById(id);
        CANVAS_DATA.ctx = CANVAS_DATA.cvs.getContext("2d");
       
    }, canvasId);

}

Canvas::~Canvas() {
    std::cout<< "canvas destroyed!" << std::endl;
}

void Canvas::clearRect(const float& x, const float& y, const float& width, const float& height) {
    EM_ASM({
        CANVAS_DATA.ctx.clearRect($0, $1, $2, $3);
        
    }, x, y, width, height);
}

void Canvas::fillRect(const float& x, const float& y, const float& width, const float& height){
     EM_ASM({
        CANVAS_DATA.ctx.fillRect($0, $1, $2, $3);
        
    }, x, y, width, height);
}

void Canvas::drawImage(const char* name, const float& x, const float& y) {
    EM_ASM({
        //  console.log(pictures[UTF8ToString($0)]);
        CANVAS_DATA.ctx.drawImage(pictures[UTF8ToString($0)], $1, $2);
    }, name, x, y);
}
void Canvas::drawImage(const char* name, const float& dX, const float& dY, const float& dWidth, const float& dHeight) {
    EM_ASM({
        CANVAS_DATA.ctx.drawImage(pictures[UTF8ToString($0)], $1, $2, $3, $4);
    }, name, dX, dY, dWidth, dHeight);
}
void Canvas::moveTo(const float& x, const float& y) {
    EM_ASM({
        CANVAS_DATA.ctx.moveTo($0, $1);
    }, x, y);
}

void Canvas::lineTo(const float& x, const float& y) {
    EM_ASM({
        CANVAS_DATA.ctx.lineTo($0, $1);
    }, x, y);
}

void Canvas::save() {
    EM_ASM(
        CANVAS_DATA.ctx.save();
    );
}

void Canvas::restore() {
    EM_ASM(
        CANVAS_DATA.ctx.restore();
    );
}

void Canvas::fillStyle(const char* color){
    EM_ASM({
        CANVAS_DATA.ctx.fillStyle = UTF8ToString($0);
    }, color);
}

void Canvas::strokeStyle(const char* color){
    EM_ASM({
        CANVAS_DATA.ctx.strokeStyle = UTF8ToString($0);
    }, color);
}


void Canvas::addEventListener(const char* name, void(*funName)()){
    std::cout << name << std::endl;
    if(!strcmp(name, "mousedown")) {
         EM_ASM({
            CANVAS_DATA.cvs.addEventListener("mousedown", wasmTable.get($0));
            console.log("mouse down");
        }, funName);
    } else if(!strcmp(name, "mousemove")){
        EM_ASM({
            CANVAS_DATA.cvs.addEventListener("mousemove", wasmTable.get($0));
            console.log("mouse move");
        }, funName);
    } else if(!strcmp(name, "mouseup")) {
        EM_ASM({
            CANVAS_DATA.cvs.addEventListener("mouseup", wasmTable.get($0));
            console.log("mouse up");
        }, funName);
    } else {
        std::cout<< "For event listener->incorrect name! " << name << std::endl;
    }
}


