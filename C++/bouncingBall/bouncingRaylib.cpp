#include <raylib.h>

struct Circle
{
    int x,y;
    int speedX,speedY;
    int radius;
    Color color;
    Circle(int x, int y, int speedX, int speedY, int radius,Color color) :
        x(x),
        y(y),
        speedX(speedX),
        speedY(speedY),
        radius(radius),
        color(color)
    {}
    void Draw() 
    {
        DrawCircle(x,y,radius,color);
    }
};

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() 
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"hello");

    Circle ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, -3, -3, 25,RED);
    
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
