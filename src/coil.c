
#include<raylib.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"game.h"
#include"food.h"
#include"state.h"

Game G;

int main()
{
	InitWindow(1000, 1000, "snake");
	Image Icon = LoadImage("SnakeIcon.png");
	SetWindowIcon(Icon);
	UnloadImage(Icon);
	SetTargetFPS(60);

	int next_x, next_y;						//目标位置								
	const char* gameover = "Game Over!";	//所需文本
	const char* start = "Press Any Key to Start";
	const char* rest = "Press R to Restart";
	const char* win = "Win !";
	const char* title = "Coil";
	const char* options = "Options";
	const char* grid = "Grid On";
	int text_x, text_y;						//文本位置
	int text_w;								//文本宽度
	double step = 0.10;						//步间隔
	Color off = { 255,255,255,255 };		//未选取的按钮颜色
	Color on = { 253,249,0,255 };			//被选取的按钮颜色
	int add;								//追加位置
	srand((unsigned int)time(0));

	Restart(&G);
	G.menu = 0;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		G.pre_dx = G.dx;
		G.pre_dy = G.dy;

		switch (G.game)
		{
		case 0:
			switch (G.menu)
			{
			case 0:
				text_w = MeasureText(title, 300);
				text_x = GetScreenWidth() / 2 - text_w / 2;
				text_y = 100;
				DrawText(title, text_x, text_y, 300, WHITE);

				if (TextButton("Play", GetScreenWidth() / 2, GetScreenHeight() / 2, 50, off, on))
				{
					G.menu = 1;
				}
				break;
			case 1:
				
				TestGrid_render(&G);
				text_w = MeasureText(options, 200);
				text_x = GetScreenWidth() / 2 - text_w / 2;
				text_y = 200;
				DrawText(options, text_x, text_y, 200, WHITE);
				
				if (TextButton("Grid On/Off", GetScreenWidth() / 2, GetScreenHeight() - 50, 50, off, on))
				{
					G.test = !G.test;
					G.menu = 1;
				}
				if (TextButton("Back", GetScreenWidth() / 2, 50, 50, off, on))
				{
					G.menu = 0;
				}
				if (TextButton("Easy", GetScreenWidth() / 2, text_y + 275, 50, off, on))
				{
					G.target = 20;
					G.menu = 2;
				}
				if (TextButton("Normal", GetScreenWidth() / 2, text_y + 350, 50, off, on))
				{
					G.target = 50;
					G.menu = 2;
				}
				if (TextButton("Hard", GetScreenWidth() / 2, text_y + 425, 50, off, on))
				{
					G.target = 100;
					G.menu = 2;
				}
				break;
			case 2:
				text_w = MeasureText(start, 50);
				text_x = GetScreenWidth() / 2 - text_w / 2;
				text_y = GetScreenHeight() / 2 - 50 / 2;
				DrawText(start, text_x, text_y, 50, WHITE);
				
				if (TextButton("Back", GetScreenWidth() / 2, 50, 50, off, on))
				{
					G.menu = 1;
				}
				
				if (GetKeyPressed())
				{
					G.game = 1;
				}
				break;
			}
			break;
		case 1:



			G.dt = GetFrameTime();											 //获取时间的帧改变量
			if (G.dt >= 0.20)												 //钳制dt限制每帧位移
			{
				G.dt = 0.20;
			}
			else if (G.dt <= 0)
			{
				G.dt = 0;
			}

			if (IsKeyDown(KEY_W))
			{
				G.pre_dx = 0;
				G.pre_dy = -1;
			}
			else if (IsKeyDown(KEY_S))
			{
				G.pre_dx = 0;				//判定移动方向：(1,0)为向右一格，(-1,0)为向左一格，(0,-1)为向上一格，(0,1)向下一格
				G.pre_dy = 1;
			}
			else if (IsKeyDown(KEY_A))
			{
				G.pre_dx = -1;
				G.pre_dy = 0;
			}
			else if (IsKeyDown(KEY_D))
			{
				G.pre_dx = 1;
				G.pre_dy = 0;
			}

			if (G.pre_dx != -G.last_dx || G.pre_dy != -G.last_dy)			//禁止原地反向移动
			{
				G.dx = G.pre_dx;
				G.dy = G.pre_dy;
			}

			G.left += G.dt;
			for (int i = 0; i < 2; i++)         //移动
			{
				if (G.left >= step)
				{
					next_x = G.x + G.dx;
					next_y = G.y + G.dy;
					if (next_x <= G.gridnum_x && next_x >= 0 && next_y <= G.gridnum_y && next_y >= 0)//判断越界
					{
						G.last_dx = G.dx;
						G.last_dy = G.dy;
						add = (G.oldest + G.body_length) % 2500;
						G.x = next_x;
						G.y = next_y;
						G.body_x[add] = G.x;
						G.body_y[add] = G.y;
						G.body_length++;

						if (G.x != G.food_x || G.y != G.food_y)
						{
							G.oldest = (G.oldest + 1) % 2500;
							G.body_length--;
						}
						else {
							Food_swapn(&G);
							G.score++;
							if (G.score >= G.target)
							{
								G.game = 2;
							}
						}

						for (int c = 0; c < G.body_length - 1; c++)			//蛇头不能撞身体
						{
							if (G.body_x[add] == G.body_x[(c + G.oldest) % 2500] && G.body_y[add] == G.body_y[(c + G.oldest) % 2500])
							{
								G.game = -1;
								break;
							}
						}
					}
					else {
						G.game = -1;
						break;
					}
					G.left = G.left - step;
				}
			}

			TestGrid_render(&G); 
			Body_render(&G);
			Food_render(&G);
			Score_render(&G);
							
			break;
		case -1:														//失败情况
			text_w = MeasureText(gameover, 100);
			text_x = GetScreenWidth() / 2 - text_w / 2;
			text_y = GetScreenHeight() / 2 - 100 / 2;
			DrawText(gameover, text_x, text_y, 100, RED);

			text_w = MeasureText(rest, 50);
			text_x = GetScreenWidth() / 2 - text_w / 2;
			text_y = (GetScreenHeight() / 2 - 50 / 2) + 100;
			DrawText(rest, text_x, text_y, 50, WHITE);

			if (IsKeyDown(KEY_R))
			{
				Restart(&G);
				G.menu = 2;
			}
			break;
		case 2:															//胜利情况
			text_w = MeasureText(win, 200);
			text_x = GetScreenWidth() / 2 - text_w / 2;
			text_y = GetScreenHeight() / 2 - 200 / 2;
			DrawText(win, text_x, text_y, 200, YELLOW);

			text_w = MeasureText(rest, 50);
			text_x = GetScreenWidth() / 2 - text_w / 2;
			text_y = (GetScreenHeight() / 2 - 50 / 2) + 100;
			DrawText(rest, text_x, text_y, 50, WHITE);

			if (IsKeyDown(KEY_R))
			{
				Restart(&G);
				G.menu = 2;
			}
			break;
		}
		EndDrawing();
	}
	CloseWindow();

	return 0;
}



