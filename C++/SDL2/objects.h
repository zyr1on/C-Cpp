#pragma once
#include"algorithms.h"
enum ObjectType{
    FILLED,
    OUTLINE
};

template<ObjectType type>
class Circle {
public:
    int x,y,radius;
    Circle(int x, int y, int r) : x(x), y(y), radius(r) {    }
    Circle() : x(0),y(0),radius(0) { }
    void render(SDL_Renderer* ren) 
    {
        drawCircle(ren, x,y,radius);
    }
private:
    constexpr static auto drawCircle = (type == FILLED) ? 
        &algorithm::drawFilledCircleBresenham : &algorithm::drawCircleBresenham;
};

template<ObjectType type>
class Rectangle {
public:
    SDL_Rect rect;
    Rectangle(int x, int y, int w, int h) : rect{x, y, w, h} {
        if (type == FILLED) {
            renderType = &Rectangle::fillRender;
        }
        else {
            renderType = &Rectangle::outlineRender;
        }
    }
    Rectangle() : rect{0, 0, 0, 0} {
        if (type == FILLED) {
            renderType = &Rectangle::fillRender;
        }
        else {
            renderType = &Rectangle::outlineRender;
        }
    }
    void render(SDL_Renderer* renderer) {
        (this->*renderType)(renderer);
    }
private:
    void (Rectangle::*renderType)(SDL_Renderer*) = nullptr;
    void fillRender(SDL_Renderer* renderer) {
        SDL_RenderFillRect(renderer, &rect);
    }
    void outlineRender(SDL_Renderer* renderer) {
        SDL_RenderDrawRect(renderer, &rect);
    }
};

void CirclePaddleCollisionLeft(Circle<FILLED>&c, SDL_Rect& rect, int& circleSpeedX,  int& circleSpeedY) 
{
    if (c.x - c.radius + circleSpeedX <= rect.x + rect.w &&
            c.y >= rect.y && c.y <= rect.y + rect.h &&
            circleSpeedX < 0) 
    {
            c.x = rect.x + rect.w + c.radius; // Paddle'ın dışına it
            circleSpeedX *= -1;
    }
}

void CirclePaddleCollisionRight(Circle<FILLED>&c, SDL_Rect& rect, int& circleSpeedX,  int& circleSpeedY) 
{
   if (c.x + c.radius + circleSpeedX >= rect.x &&
            c.y >= rect.y && c.y <= rect.y + rect.h &&
            circleSpeedX > 0) {
            
            c.x = rect.x - c.radius; // Paddle'ın dışına it
            circleSpeedX *= -1;   
    }
}
