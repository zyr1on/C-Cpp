#include<SDL2/SDL.h>
#include"objects.h"
#include<iostream>

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
    int ballSpeedX = 5;
    int ballSpeedY = 5;

    SDL_Rect rect1{50,300,50,250};
    SDL_Rect rect2{800-50,300,50,250}; // rightPaddle

    //Rectangle<FILLED> rect3(400,400,200,55);

    Uint32 frameStart, frameTime;

    while (isRunning)
    {
        frameStart = SDL_GetTicks();

        ball.x += ballSpeedX;
        ball.y += ballSpeedY;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                isRunning = false;            
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W])
            rect1.y -= 5;
        if (currentKeyStates[SDL_SCANCODE_S])
            rect1.y += 5;

        if (currentKeyStates[SDL_SCANCODE_UP])
            rect2.y -= 5;
        if (currentKeyStates[SDL_SCANCODE_DOWN])
            rect2.y += 5;

        // bounce
        if(ball.y + ball.radius >= 600 || ball.y - ball.radius <= 0)
            ballSpeedY *= -1;


        CirclePaddleCollisionLeft(ball,rect1,ballSpeedX,ballSpeedY);
        CirclePaddleCollisionRight(ball,rect2,ballSpeedX,ballSpeedY);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer,&rect1);
            SDL_RenderFillRect(renderer,&rect2);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            ball.render(renderer);
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
