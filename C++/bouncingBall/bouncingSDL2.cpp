#include<SDL2/SDL.h>
#include<iostream>
#include<cmath>

struct Circle {
public:
    int x,y,speedX,speedY,radius;
    Circle(int x, int y, int speedX, int speedY, int r): 
    x(x), 
    y(y), 
    speedX(speedX),
    speedY(speedY),
    radius(r) 
    {}
    void draw(SDL_Renderer* renderer) {
        for (int cy = -radius; cy <= radius; cy++) {
            int cx = (int)sqrt(radius * radius - cy * cy);  //  x*x + y*y = r*r -> x = sqrt(r*r-y*y)
            SDL_RenderDrawLine(renderer, x - cx, y + cy, cx + x, cy + y);
        }
    }
};

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
bool isRunning = false;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Bounce With SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    isRunning = true;
    
    Circle ball(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,-3,-3,25);
    
    while (isRunning)
    {
        ball.x += ball.speedX;
        ball.y += ball.speedY;
        
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                isRunning = false;
        
        if(ball.y + ball.radius >= SCREEN_HEIGHT || ball.y - ball.radius <= 0)
            ball.speedY *= -1;
        if(ball.x + ball.radius >= SCREEN_WIDTH || ball.x - ball.radius <= 0)
            ball.speedX *= -1;
        
        SDL_SetRenderDrawColor(renderer, 51, 77, 77, 255);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            ball.draw(renderer);
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
// total 56 lines
