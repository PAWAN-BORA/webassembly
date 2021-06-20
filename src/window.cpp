#include "window.h"
#include <emscripten.h>
#include <iostream>



Window::Window(/* args */)
{
    std::cout << "window object created\n";
}

Window::~Window()
{
    std::cout << "window object destroyed\n";
}



void Window::onResize(void(*res)()){
    EM_ASM({
        window.onresize = ()=>{
            wasmTable.get($0)();
        }
    }, res);
} 
void Window::requestAnimationFrame(void(*loop)()) {
    EM_ASM({
        function tick() {
            wasmTable.get($0)();
            window.requestAnimationFrame(tick);
        }
        tick();
    }, loop);
  
}
void Window::addEventListener(const char* name, void(*funName)()){
    if(!strcmp(name, "mousedown")) {
        EM_ASM({
            window.addEventListener("mousedown", wasmTable.get($0));
        }, funName);
    } else if(!strcmp(name, "mousemove")){
        EM_ASM({
            window.addEventListener("mousemove", wasmTable.get($0));
        }, funName);
    } else if(!strcmp(name, "mouseup")) {
        EM_ASM({
            window.addEventListener("mouseup", wasmTable.get($0));
        }, funName);
    } else {
        std::cout<< "For event listener->incorrect name! " << name << std::endl;
    }
}
