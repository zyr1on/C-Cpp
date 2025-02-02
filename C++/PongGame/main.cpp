#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

struct Ball
{
    float x,y;
    float speedX,speedY;
    float radius;
    void Draw() 
    {
        DrawCircle((int)x,(int)y,radius,WHITE);
    }
};


struct Paddle{
    float x,y;
    float speed;
    float width,height;
    Rectangle GetRect() {
        return Rectangle {x-width / 2, y-width / 2, 10, 100};
    }
    void Draw()
    {
        DrawRectangleRec(GetRect(),WHITE);
    }
};

int main() 
{
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"hello");
    SetTargetFPS(60);

    Ball ball;
    ball.x = SCREEN_WIDTH / 2.0f;
    ball.y = SCREEN_HEIGHT / 2.0f;
    ball.radius = 5;
    ball.speedX = 300;
    ball.speedY = 300;

    Paddle leftPaddle;
    Paddle rightPaddle;
    leftPaddle.x = 50;
    rightPaddle.x = SCREEN_WIDTH - 50;
    leftPaddle.y = rightPaddle.y =  SCREEN_HEIGHT / 2;
    leftPaddle.width = rightPaddle.width = 10;
    leftPaddle.height = rightPaddle.height = 100;
    leftPaddle.speed = rightPaddle.speed = 550;
    
    const char* winnerText = nullptr;

    while(!WindowShouldClose()) 
    {

        ball.x += ball.speedX * GetFrameTime();
        ball.y += ball.speedY * GetFrameTime();
        
        if(ball.y + ball.radius >= SCREEN_HEIGHT || (ball.y - ball.radius) <= 0)
            ball.speedY *= -1;
        
        if(IsKeyDown(KEY_W))
            leftPaddle.y -= leftPaddle.speed * GetFrameTime();
        if(IsKeyDown(KEY_S))
            leftPaddle.y += leftPaddle.speed * GetFrameTime();
        if(IsKeyDown(KEY_UP))
            rightPaddle.y -= rightPaddle.speed * GetFrameTime();
        if(IsKeyDown(KEY_DOWN))
            rightPaddle.y += rightPaddle.speed * GetFrameTime();
        
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, leftPaddle.GetRect()))
            if(ball.speedX < 0) 
            {
                ball.speedX *= -1.05f;
                ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX; 
            }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, rightPaddle.GetRect()))
                if(ball.speedX > 0) 
                {
                    ball.speedX *= -1.05f;
                    ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
                }

        if(ball.x < 0)
            winnerText = "Right is winner";
        if(ball.x > SCREEN_WIDTH)
            winnerText = "Left is Winner";

        if(winnerText && IsKeyPressed(KEY_SPACE)) 
        {
            ball.x = ball.y = SCREEN_WIDTH / 2;
            ball.speedX = ball.speedY = 300;
            winnerText = nullptr;
        }
    
        BeginDrawing();
            ClearBackground(BLACK);
            ball.Draw();
            
            leftPaddle.Draw();
            rightPaddle.Draw();

            if(winnerText)
                DrawText(winnerText,200,GetScreenHeight() / 2 - 30, 60,YELLOW);

        EndDrawing();
    }
}
