#include<SDL2/SDL.h>
#include"algorithms.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
bool isRunning = false;
const int FPS = 60;
const int frameDelay = 1000 / FPS;

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL Circle Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, 0, -1);
    isRunning = true;

    int centerX = 400;
    int centerY = 300;
    int radius = 10;
    int circleSpeedX = 5;
    int circleSpeedY = 5;

    constexpr auto drawCircle = algorithm::drawFilledCircleBresenham; // void (*drawCircle)(SDL_Renderer*, int, int, int) = &algorithm::drawFilledCircleBresenham
    Uint32 frameStart, frameTime;

    while (isRunning)
    {
        frameStart = SDL_GetTicks();

        centerX += circleSpeedX;
        centerY += circleSpeedY;

        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                isRunning = false;
		
        if(centerY + radius >= 600 || centerY - radius <= 0)
            circleSpeedY *= -1;
        if(centerX + radius >= 800 || centerX - radius <= 0)
            circleSpeedX *= -1;
       
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            drawCircle(renderer,centerX,centerY,radius);

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
