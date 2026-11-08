#include<stdio.h>
#include<raylib.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	InitWindow(1000, 1000, "snake");
	Image Icon = LoadImage("SnakeIcon.png");
	SetWindowIcon(Icon);
	UnloadImage(Icon);
	SetTargetFPS(60);

	int body_x[2500], body_y[2500];                       //定义数组body_x,body_y作为计算蛇身位置时的临时变量
	int body_length = 1;					//蛇身长度
	int oldest = 0;							//最旧下标
	int x, y;									//定义x,y作为计算位置的临时变量
	double dt;								//定义dt储存上一帧耗
	double left = 0;						//定义left储存消耗的时间
	int r = 20;
	int gridnum_x, gridnum_y;				//换算为格子坐标后的最大索引
	int gridLength = (int)(r);				//格子边长
	int dx = 1, dy = 0;						//生效移动方向及移动量
	int pre_dx = 1, pre_dy = 0;				//下一移动方向及移动量
	int last_dx = 0, last_dy = 0;			//上一移动方向及移动量
	int next_x, next_y;						//目标位置
	int game = 0;							//游戏状态判定变量
	const char* gameover = "Game Over!";	//所需文本
	const char* start = "Press Any Key to Start";
	const char* rest = "Press R to Restart";
	const char* win = "Win !";
	int text_x, text_y;						//文本位置
	int text_w;								//文本宽度
	Color test = { 82,82,82,255 };			//网格颜色（测试用）
	int add;								//记录追加位置
	int food_x, food_y;						//食物的位置
	srand((unsigned int)time(0));

	x = 24;									//初始位置居中
	y = 24;

	for (int k = 0; k < body_length; k++)
	{
		body_x[k] = x - (body_length - 1 - k) * dx;
		body_y[k] = y - (body_length - 1 - k) * dy;
	}

	next_x = x;								//初始化目标位置
	next_y = y;

	gridnum_x = (int)floor(GetScreenWidth() / gridLength) - 1;
	gridnum_y = (int)floor(GetScreenHeight() / gridLength) - 1;      //像素坐标换算为格子坐标

	food_x = rand() % (gridnum_x + 1);							//生成初始食物位置
	food_y = rand() % (gridnum_y + 1);
	while (food_x == x && food_y == y)
	{
		food_x = rand() % (gridnum_x + 1);
		food_y = rand() % (gridnum_y + 1);
	}

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		pre_dx = dx;
		pre_dy = dy;

		switch (game)
		{
		case 0:
			text_w = MeasureText(start, 50);
			text_x = GetScreenWidth() / 2 - text_w / 2;		//文本水平居中
			text_y = GetScreenHeight() / 2 - 50 / 2;
			DrawText(start, text_x, text_y, 50, WHITE);
			if (GetKeyPressed())
			{
				game = 1;
			}
			break;
		case 1:

			for (int i = 0;i <= gridnum_x + 1; i++)		//绘制测试用网格
			{
				DrawLine(i * gridLength, 0, i * gridLength, GetScreenHeight(), test);
				DrawLine(0, i * gridLength, GetScreenWidth(), i * gridLength, test);
			}

			dt = GetFrameTime();											 //获取时间的帧改变量
			if (dt >= 0.20)													 //钳制dt限制每帧位移
			{
				dt = 0.20;
			}
			else if (dt <= 0)
			{
				dt = 0;
			}

			if (IsKeyDown(KEY_W))
			{
				pre_dx = 0;
				pre_dy = -1;
			}
			else if (IsKeyDown(KEY_S))
			{
				pre_dx = 0;				//判定移动方向：(1,0)为向右一格，(-1,0)为向左一格，(0,-1)为向上一格，(0,1)向下一格
				pre_dy = 1;
			}
			else if (IsKeyDown(KEY_A))
			{
				pre_dx = -1;
				pre_dy = 0;
			}
			else if (IsKeyDown(KEY_D))
			{
				pre_dx = 1;
				pre_dy = 0;
			}

			if (pre_dx != -last_dx || pre_dy != -last_dy)			//禁止原地反向移动
			{
				dx = pre_dx;
				dy = pre_dy;
			}

			left += dt;
			for (int i = 0; i < 2; i++)         //移动
			{
				if (left >= 0.20)
				{
					next_x = x + dx;
					next_y = y + dy;
					if (next_x <= gridnum_x && next_x >= 0 && next_y <= gridnum_y && next_y >= 0)//判断越界
					{
						last_dx = dx;
						last_dy = dy;
						add = (oldest + body_length) % 2500;
						x = next_x;
						y = next_y;
						body_x[add] = x;
						body_y[add] = y;
						body_length++;

						if (x != food_x || y != food_y)
						{
							oldest = (oldest + 1) % 2500;
							body_length--;
						}
						else {
							int ok = 0;
							int tries = 0;
							while(!ok && tries < 100)
							{
								food_x = rand() % (gridnum_x + 1);							//生成新食物位置不能与蛇身重合
								food_y = rand() % (gridnum_y + 1);
								ok = 1;

								for(int a = 0;a < body_length; a++)
								{
									if (body_x[(a + oldest) % 2500] == food_x && body_y[(a + oldest) % 2500] == food_y)
									{
										ok = 0;
										break;
									}
								}
								tries++;
							}
							if (!ok)
							{
								game = 2;
							}
						}

						for (int c = 0; c < body_length - 1; c++)			//蛇头不能撞身体
						{
							if (body_x[add] == body_x[(c + oldest) % 2500] && body_y[add] == body_y[(c + oldest) % 2500])
							{
								game = -1;
								break;
							}
						}
					}
					else {
						game = -1;
						break;
					}
					left = left - 0.20;
				}
			}

			for (int j = 0; j < body_length; j++)													 //绘制蛇身
			{
				DrawRectangle((int)(body_x[(oldest + j) % 2500] * gridLength), (int)(body_y[(oldest + j) % 2500] * gridLength), r, r, WHITE);
			}
			DrawCircle(food_x * gridLength + gridLength / 2, food_y * gridLength + gridLength / 2, (float)(r / 5), YELLOW);//绘制食物
			break;
		case -1:
			text_w = MeasureText(gameover, 100);
			text_x = GetScreenWidth() / 2 - text_w / 2;
			text_y = GetScreenHeight() / 2 - 100 / 2;
			DrawText(gameover, text_x, text_y, 100, RED);

			text_w = MeasureText(rest, 50);
			text_x = GetScreenWidth() / 2 - text_w / 2;
			text_y = (GetScreenHeight() / 2 - 50 / 2) + 100;
			DrawText(rest, text_x, text_y, 50, WHITE);
			if (IsKeyPressed(KEY_R))				//重开
			{
				game = 0;

				x = 24;								//参数初始化
				y = 24;

				left = 0;

				dx = 1;
				dy = 0;

				last_dx = 0;
				last_dy = 0;

				oldest = 0;
				body_length = 1;
				for (int k = oldest; k < body_length; k++)
				{
					body_x[k] = x - (body_length - 1 - k) * dx;
					body_y[k] = y - (body_length - 1 - k) * dy;
				}

				food_x = rand() % (gridnum_x + 1);
				food_y = rand() % (gridnum_y + 1);
				while (food_x == x && food_y == y)
				{
					food_x = rand() % (gridnum_x + 1);
					food_y = rand() % (gridnum_y + 1);
				}
			}
			break;
		case 2:
			text_w = MeasureText(win, 200);
			text_x = GetScreenWidth() / 2 - text_w / 2;
			text_y = GetScreenHeight() / 2 - 200 / 2;
			DrawText(win, text_x, text_y, 200, YELLOW);

			text_w = MeasureText(rest, 50);
			text_x = GetScreenWidth() / 2 - text_w / 2;
			text_y = (GetScreenHeight() / 2 - 50 / 2) + 100;
			DrawText(rest, text_x, text_y, 50, WHITE);
			if (IsKeyPressed(KEY_R))				//重开
			{
				game = 0;

				x = 24;								//参数初始化
				y = 24;

				left = 0;

				dx = 1;
				dy = 0;

				last_dx = 0;
				last_dy = 0;

				oldest = 0;
				body_length = 1;
				for (int k = oldest; k < body_length; k++)
				{
					body_x[k] = x - (body_length - 1 - k) * dx;
					body_y[k] = y - (body_length - 1 - k) * dy;
				}

				food_x = rand() % (gridnum_x + 1);
				food_y = rand() % (gridnum_y + 1);
				while (food_x == x && food_y == y)
				{
					food_x = rand() % (gridnum_x + 1);
					food_y = rand() % (gridnum_y + 1);
				}
			}
			break;
		}
		EndDrawing();
	}
	CloseWindow();

	return 0;
}