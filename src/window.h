#pragma once

// typedef ;
class Window
{
private:
    /* data */
public:
    Window(/* args */);
    ~Window();
   
    void onResize(void(*resize)());
    void requestAnimationFrame(void(*loop)());
    void addEventListener(const char* name, void(*funName)()); 
};


