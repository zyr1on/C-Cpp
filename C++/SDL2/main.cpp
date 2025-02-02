#include<iostream>
#include<SDL2/SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
bool isRunning = false;

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,0,-1);
    isRunning = true;
    while(isRunning) 
    {
        while(SDL_PollEvent(&event)) 
        {
            if(event.type == SDL_QUIT)
                isRunning= false;
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
