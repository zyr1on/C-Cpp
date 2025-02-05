#pragma once
#include<SDL2/SDL.h>
#include"objects.h"


bool checkCollision(SDL_Rect& a, SDL_Rect& b) 
{
    return (a.x + a.w > b.x) &&
           (a.x < b.x + b.w) &&
           (a.y + a.h > b.y) &&
           (a.y < b.y + b.h);
}

template<ObjectType T>
bool checkCollision(Circle<T>& c, SDL_Rect& rect) 
{
    float closestX, closestY;
    if(c.x < rect.x) closestX = rect.x;
    else if(c.x > rect.x + rect.w) closestX = rect.x + rect.w;
    else closestX = c.x;
    
    if(c.y < rect.y) closestY = rect.y;
    else if(c.y > rect.y + rect.h) closestY = rect.y + rect.h;
    else closestY = c.y;
    float dx = closestX - c.x;
    float dy = closestY - c.y;
    return (dx*dx + dy*dy) <= (c.radius*c.radius);
}

template<ObjectType T1,ObjectType T2>
bool checkCollision(Circle<T1>& c1, Circle<T2>& c2) 
{
    int dx = c2.x - c1.x;
    int dy = c2.y - c1.y;
    int distance = dx*dx + dy*dy;
    int radius = c1.radius + c2.radius;
    return distance <= (radius*radius);
}
