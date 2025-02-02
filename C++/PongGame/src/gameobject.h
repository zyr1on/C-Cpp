#pragma once
#include"raylib.h"

struct Ball
{
    float x,y;
    float speedX,speedY;
    float radius;
    Ball(float x, float y, float speedX, float speedY, float radius) :
        x(x),
        y(y),
        speedX(speedX),
        speedY(speedY),
        radius(radius)
    {}
    void Draw() 
    {
        DrawCircle((int)x,(int)y,radius,WHITE);
    }
};

struct Paddle{
    float x,y;
    float speed;
    float width,height;
    Paddle(float x, float y,float speed, float width, float height) :
        x(x),
        y(y),
        speed(speed),
        width(width),
        height(height)
    {}
    Rectangle GetRect() {
        return Rectangle {x-width / 2, y-width / 2, 10, 100};
    }
    void Draw()
    {
        DrawRectangleRec(GetRect(),WHITE);
    }
};
