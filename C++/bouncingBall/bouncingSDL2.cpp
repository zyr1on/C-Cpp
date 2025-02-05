#include<SDL2/SDL.h>
#include<iostream>
#include<cmath>

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius); // polar

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
bool isRunning = false;

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL Circle Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    isRunning = true;

    int xPos = 400;
    int yPos = 300;
    int radius = 20;
    int ballSpeedX = -3;
    int ballSpeedY = -3;

    while (isRunning)
    {
        xPos += ballSpeedX;
        yPos += ballSpeedY;
        
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                isRunning = false;
        // bounce
        if(yPos +  radius >= 600 || yPos - radius <= 0)
            ballSpeedY *= -1;
        if(xPos + radius >= 800 || xPos - radius <= 0)
            ballSpeedX *= -1;

        SDL_SetRenderDrawColor(renderer, 51, 77, 77, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            drawCircle(renderer,xPos,yPos,25);
        
        SDL_RenderPresent(renderer);   
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius)
{
    for (int y = -radius; y <= radius; y++) {
        int x = (int)sqrt(radius * radius - y * y);  //  x*x + y*y = r*r -> x = sqrt(r*r-y*y)
        SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
    }
}
