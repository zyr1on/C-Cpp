#include<SDL2/SDL.h>
#include"objects.h"

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

    Circle<FILLED> ball(400,300,10);
    // Circle<FILLED/UNFILLED> ball(xPos,yPos,radius);
    int circleSpeedX = 5;
    int circleSpeedY = 5;

    Uint32 frameStart, frameTime;

    while (isRunning)
    {
        frameStart = SDL_GetTicks();

        ball.x += circleSpeedX;
        ball.y += circleSpeedY;

        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                isRunning = false;

        if(ball.y + ball.radius >= 600 || ball.y - ball.radius <= 0)
            circleSpeedY *= -1;
        if(ball.x + ball.radius >= 800 || ball.x - ball.radius <= 0)
            circleSpeedX *= -1;
       
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            ball.draw(renderer);
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
