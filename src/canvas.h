#pragma once
// #include <iostream>
// #include <string>
// typedef struct HTMLCanvasElement HTMLCanvasElement;
// typedef struct CanvasRenderingContext2D CanvasRenderingContext2D;

class Canvas {
private:
    /* data */
    int width;
    int height;
     
     
public:
    Canvas(const char*  canvaId);
    ~Canvas();
    void clearRect(const float& x, const float& y, const float& width, const float& height);
    void fillRect(const float& x, const float& y, const float& width, const float& height);
    void save();
    void restore();
    void moveTo(const float& x, const float& y);
    void lineTo(const float& x, const float& y);
    void fillStyle(const char* color);
    void strokeStyle(const char* color);
    void drawImage(const char* name, const float& x, const float& y);
    void drawImage(const char* name, const float& dX, const float& dY, const float& dWidth, const float& dHeight);
    void drawImage(const char* name, const float& sX, const float& sY, const float& sWidth, const float& sHeight, const float& dX, const float& dY, const float& dWidth, const float& dHeight);
    void addEventListener(const char* name, void(*funName)()); 
};



