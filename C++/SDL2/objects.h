#include"algorithms.h"
#pragma once
enum ObjectType{
    FILLED,
    OUTLINE
};
template<ObjectType type>
class Circle {
public:
    int x,y,radius;
    Circle(int x, int y, int r) : x(x), y(y), radius(r) {    }
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

bool CheckCollisionCircleRect(Circle<FILLED>& c, SDL_Rect& rect) 
{
    float closestX, closestY;
    if(c.x < rect.x) {
        closestX = rect.x;
    }
    else if(c.x > rect.x + rect.w){
        closestX = rect.x + rect.w;
    }
    else {
        closestX = c.x;
    }
    if(c.y < rect.y) {
        closestY = rect.y;
    }
    else if(c.y > rect.y + rect.h){
        closestY = rect.y + rect.h;
    }
    else {
        closestY = c.y;
    }
    float dx = closestX - c.x;
    float dy = closestY - c.y;
    return (dx*dx + dy*dy) <= (c.radius*c.radius);
}

bool CirclePaddleCollisionLeft(Circle<FILLED>&c, SDL_Rect& rect, int& circleSpeedX,  int& circleSpeedY) 
{
    if (c.x - c.radius + circleSpeedX <= rect.x + rect.w &&
            c.y >= rect.y && c.y <= rect.y + rect.h &&
            circleSpeedX < 0) 
    {
            c.x = rect.x + rect.w + c.radius; // Paddle'ın dışına it
            circleSpeedX *= -1;
    }

}
bool CirclePaddleCollisionRight(Circle<FILLED>&c, SDL_Rect& rect, int& circleSpeedX,  int& circleSpeedY) 
{
   if (c.x + c.radius + circleSpeedX >= rect.x &&
            c.y >= rect.y && c.y <= rect.y + rect.h &&
            circleSpeedX > 0) {
            
            c.x = rect.x - c.radius; // Paddle'ın dışına it
            circleSpeedX *= -1;
    }

}
