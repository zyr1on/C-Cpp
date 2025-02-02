#pragma once
#include<SDL2/SDL.h>
#include<cmath> 

namespace algorithm {
    void drawCircleBresenham(SDL_Renderer* renderer, int centerX, int centerY, int radius) 
    {
        int x = radius;
        int y = 0;
        int p = 1 - radius;

        while (x >= y) {
            SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY + x); 
            SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
            y++;
            if (p < 0)
                p += 2 * y + 1;
            else {
                x--;
                p += 2 * (y - x) + 1;
            }
        }
    }
    void drawCirclePolar(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
        const float PI = 3.14159265;
        for (float theta = 0.0f; theta < 2 * PI; theta += 0.01f) {
            int x = centerX + radius * cos(theta);
            int y = centerY + radius * sin(theta);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    void drawFilledCirclePolar(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
        for (int y = -radius; y <= radius; y++) {
            int x = (int)sqrt(radius * radius - y * y);  //  x*x + y*y = r*r -> x = sqrt(r*r-y*y)
            SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
        }
    }
    void drawFilledCircleBresenham(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
        int x = radius;
        int y = 0;
        int p = 1 - radius;
       
        while (x >= y) {
            SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y); 
            SDL_RenderDrawLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y); 
            SDL_RenderDrawLine(renderer, centerX - y, centerY + x, centerX + y, centerY + x); 
            SDL_RenderDrawLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);
            
            SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
            y++;
            if (p < 0)
                p += 2 * y + 1;
            else {
                x--;
                p += 2 * (y - x) + 1;
            }
        }
    }
}
