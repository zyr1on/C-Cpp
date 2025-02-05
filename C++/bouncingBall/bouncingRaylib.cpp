#include <raylib.h>
//#include"gameobject.h"

struct Ball
{
    float x,y;a#include <raylib.h>
//#include"gameobject.h"

struct Circle
{
    float x,y;
    float speedX,speedY;
    float radius;
    Color color;
    Circle(float x, float y, float speedX, float speedY, float radius,Color color) :
        x(x),
        y(y),
        speedX(speedX),
        speedY(speedY),
        radius(radius),
        color(color)

    {}
    void Draw() 
    {
        DrawCircle((int)x,(int)y,radius,color);
    }
};

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() 
{
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"hello");
    SetConfigFlags(FLAG_VSYNC_HINT);

    Circle ball(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, -0.025f, -0.025f, 20.0f,RED);
    
    while(!WindowShouldClose()) 
    {
        ball.x += ball.speedX;
        ball.y += ball.speedY;
        
        if(ball.y + ball.radius >= SCREEN_HEIGHT || (ball.y - ball.radius) <= 0)
            ball.speedY *= -1;
        if(ball.x + ball.radius >= SCREEN_WIDTH || (ball.x - ball.radius) <= 0)
            ball.speedX *= -1;
        
        BeginDrawing();
            ClearBackground(Color{51, 77, 77, 255});
            ball.Draw();
        EndDrawing();
    }
}
    float speedX,speedY;
    float radius;
    Color color;
    Ball(float x, float y, float speedX, float speedY, float radius,Color color) :
        x(x),
        y(y),
        speedX(speedX),
        speedY(speedY),
        radius(radius),
        color(color)

    {}
    void Draw() 
    {
        DrawCircle((int)x,(int)y,radius,color);
    }
};

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() 
{
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"hello");
    SetConfigFlags(FLAG_VSYNC_HINT);

    Ball ball(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, -0.025f, -0.025f, 20.0f,RED);
    
    while(!WindowShouldClose()) 
    {
        ball.x += ball.speedX;
        ball.y += ball.speedY;
        
        if(ball.y + ball.radius >= SCREEN_HEIGHT || (ball.y - ball.radius) <= 0)
            ball.speedY *= -1;
        if(ball.x + ball.radius >= SCREEN_WIDTH || (ball.x - ball.radius) <= 0)
            ball.speedX *= -1;
        
        BeginDrawing();
            ClearBackground(Color{51, 77, 77, 255});
            ball.Draw();
        EndDrawing();
    }
}
