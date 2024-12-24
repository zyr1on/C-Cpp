#include"include/SDL2/SDL.h"

// g++ basic_window.cpp -I include -L lib -l SDL2

#undef main

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
bool isRunning = false;

const int FPS=60;
const int frameDelay = 1000 / FPS;

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,0);
    renderer = SDL_CreateRenderer(window,-1,0);
    isRunning=true;
    while(isRunning) 
    {
        Uint32 frameStart = SDL_GetTicks();
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                isRunning = false;
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
