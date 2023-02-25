#include "raylib.h"
#include <iostream>
#include <math.h>
#include <string>
using namespace std;
struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int)x, (int)y, radius, ORANGE);
	}
};
struct Paddle
{
	float x, y;
	float speed;
	float width, height;
	Rectangle GetRect()
	{
		return Rectangle{x - width / 2, y - height / 2, 10, 100};
	}
	void Draw()
	{
		DrawRectangleRec(GetRect(), BLUE);
	}
};
int main()
{
	int c = 0;
	InitWindow(800, 500, "Pong_test_window");
	SetWindowState(FLAG_VSYNC_HINT | FLAG_WINDOW_MAXIMIZED);
	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenWidth() / 2.0f;
	ball.radius = 5;
	ball.speedX = 250;
	ball.speedY = 250;

	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;

	const char* winnerText = nullptr;
	//const char* score = nullptr;
	char score;
	
	Sound sound = LoadSound("D:\collide_sound.wav");

	while (!WindowShouldClose())
	{
		//ball things
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();
		if (ball.x >= GetScreenWidth())
		{
			ball.speedX = 0;
			ball.speedY = 0;
		}
		if (ball.x <= 0)
		{
			ball.speedX = 0;
			ball.speedY = 0;
		}
		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.speedY *= -1;
		}

		//paddle movement
		//left paddle
		if(winnerText!="GAME OVER !")
		{
			if (IsKeyDown(KEY_W))
			{
				leftPaddle.y -= leftPaddle.speed * GetFrameTime();
			}
			if (IsKeyDown(KEY_S))
			{
				leftPaddle.y += leftPaddle.speed * GetFrameTime();
			}
			//right paddle
			if (IsKeyDown(KEY_UP))
			{
				rightPaddle.y -= leftPaddle.speed * GetFrameTime();
			}
			if (IsKeyDown(KEY_DOWN))
			{
				rightPaddle.y += leftPaddle.speed * GetFrameTime();
			}
		}
		if (IsKeyPressed(KEY_SPACE))
		{
			PlaySound(sound);
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect()))
		{
			PlaySound(sound);
			c = c + 1;
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.0001f;
				ball.speedY *= 1.0001f;
			}
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect()))
		{
			PlaySound(sound);
			c += 1;
			if(ball.speedX > 0)
			{
				ball.speedX *= -1.0001f;
				ball.speedY *= 1.0001f;
			}		
		}
		
		if (ball.x < 0 || ball.x > GetScreenWidth())
		{
			winnerText = "GAME OVER !";
		}
		if (winnerText && IsKeyPressed(KEY_SPACE)|| winnerText && IsKeyPressed(KEY_ENTER))
		{
			c = 0;
			ball.x = GetScreenWidth() / 2.0f;
			ball.y = GetScreenWidth() / 2.0f;
			ball.radius = 5;
			ball.speedX = 250;
			ball.speedY = 250;
			winnerText = nullptr;
			rightPaddle.x = GetScreenWidth() - 50;
			rightPaddle.y = GetScreenHeight() / 2;
			leftPaddle.x = 50;
			leftPaddle.y = GetScreenHeight() / 2;
		}
		BeginDrawing();
		ClearBackground(BLANK);

		ball.Draw();
		leftPaddle.Draw();
		rightPaddle.Draw();
		std::string s= std::to_string(c);
		const char* score = s.c_str();
		if (winnerText)
		{
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth()/2 - textWidth/2, GetScreenHeight() / 2 - 30, 60, RED);//game over
			DrawText("Score : ", GetScreenWidth() / 2 - textWidth / 2, (GetScreenHeight() / 2 - 30) + 60, 30, GREEN);//score text
			
			DrawText("Press ENTER or SPACEBAR", GetScreenWidth() / 2 - textWidth / 2, ((GetScreenHeight() / 2 - 30) + 60)+40, 25, YELLOW);//instructions
			DrawText("to start again", GetScreenWidth() / 2 - textWidth / 2, ((GetScreenHeight() / 2 - 30) + 60) + 65, 25, YELLOW);//instruction line 2
		
			if (c >= 50)
			{
				DrawText(score, (GetScreenWidth() / 2 - textWidth / 2) + 120, (GetScreenHeight() / 2 - 30) + 60, 30, GREEN);//score
			}
			else if (c < 25 && c>10)
				DrawText(score, (GetScreenWidth() / 2 - textWidth / 2) + 120, (GetScreenHeight() / 2 - 30) + 60, 30, ORANGE);//score
			else
				DrawText(score, (GetScreenWidth() / 2 - textWidth / 2) + 120, (GetScreenHeight() / 2 - 30) + 60, 30, RED);//score
		}
		DrawText("Pong v1.0", GetScreenWidth() - 67, GetScreenHeight() - 20, 13, GRAY);//version
		DrawFPS(20, 20);
		EndDrawing();
	}
	UnloadSound(sound);
	CloseWindow();
	return 0;
}