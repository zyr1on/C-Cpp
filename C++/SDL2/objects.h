#pragma once
#include"algorithms.h"

enum CircleType{
    FILLED,
    NOTFILLED
};
template<CircleType type>
class Circle {
public:
    int x,y;
    int radius;

    Circle(int x, int y, int r) : x(x), y(y), radius(r) {}
    void draw(SDL_Renderer* ren) 
    {
        drawCircle(ren, x,y,radius);
    }
private:
    constexpr static auto drawCircle = (type == FILLED) ? 
        &algorithm::drawFilledCircleBresenham : &algorithm::drawCircleBresenham;

};
