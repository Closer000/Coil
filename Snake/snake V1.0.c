#include<stdio.h>
#include<raylib.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

struct Game
{
	int x, y;								//定义x,y作为计算位置的临时变量
	double left;							//定义left储存消耗的时间
	double dt;								//定义dt储存上一帧耗时
	int dx, dy;								//生效移动方向及移动量
	int pre_dx, pre_dy;						//下一移动方向及移动量
	int last_dx, last_dy;					//上一移动方向及移动量
	int body_x[2500], body_y[2500];         //定义数组body_x,body_y作为计算蛇身位置时的临时变量
	int body_length;						//蛇身长度
	int oldest;								//最旧下标
	int food_x, food_y;						//食物的位置
	int game;								//游戏状态判定变量
	int gridnum_x, gridnum_y;				//换算为格子坐标后的最大索引
	int gridLength;							//格子边长
}G;

void Restart(struct Game *p);
int Food(struct Game *p);
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
	int text_x, text_y;						//文本位置
	int text_w;								//文本宽度
	Color test = { 82,82,82,255 };			//网格颜色（测试用）
	int add;								//记录追加位置
	srand((unsigned int)time(0));

	Restart(&G);
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		G.pre_dx = G.dx;
		G.pre_dy = G.dy;

		switch (G.game)
		{
		case 0:
			text_w = MeasureText(start, 50);
			text_x = GetScreenWidth() / 2 - text_w / 2;		//文本水平居中
			text_y = GetScreenHeight() / 2 - 50 / 2;
			DrawText(start, text_x, text_y, 50, WHITE);
			if (GetKeyPressed())
			{
				G.game = 1;
			}
			break;
		case 1:

			for (int i = 0;i <= G.gridnum_x + 1; i++)		//绘制测试用网格
			{
				DrawLine(i * G.gridLength, 0, i * G.gridLength, GetScreenHeight(), test);
				DrawLine(0, i * G.gridLength, GetScreenWidth(), i * G.gridLength, test);
			}

			G.dt = GetFrameTime();											 //获取时间的帧改变量
			if (G.dt >= 0.20)													 //钳制dt限制每帧位移
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
				if (G.left >= 0.20)
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
							if (!Food(&G))
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
					G.left = G.left - 0.20;
				}
			}

			for (int j = 0; j < G.body_length; j++)													 //绘制蛇身
			{
				DrawRectangle((int)(G.body_x[(G.oldest + j) % 2500] * G.gridLength), (int)(G.body_y[(G.oldest + j) % 2500] * G.gridLength), G.gridLength, G.gridLength, WHITE);
			}
			DrawCircle(G.food_x * G.gridLength + G.gridLength / 2, G.food_y * G.gridLength + G.gridLength / 2, (float)(G.gridLength / 5), YELLOW);//绘制食物
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
			
			if (IsKeyDown (KEY_R))
			{
				Restart(&G);
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
			}
			break;
		}
		EndDrawing();
	}
	CloseWindow();

	return 0;
}

void Restart(struct Game *p)
{
	p->gridLength = 40;
	p->gridnum_x = GetScreenWidth() / p->gridLength - 1;
	p->gridnum_y = GetScreenHeight() / p->gridLength - 1;

	p->x = p->gridnum_x / 2;
	p->y = p->gridnum_y / 2;

	p->left = 0;
	
	p->dx = 1;
	p->dy = 0;
	p->pre_dx = 1;
	p->pre_dy = 0;
	p->last_dx = 0;
	p->last_dy = 0;

	p->oldest = 0;
	p->body_length = 1;

	for (int i = 0; i < p->body_length;i++)
	{
		p->body_x[(i + p->oldest) % 2500] = p->x - (p->body_length - 1 - i) * p->dx;
		p->body_y[(i + p->oldest) % 2500] = p->y - (p->body_length - 1 - i) * p->dy;
	}

	Food(p);

	p->game = 0;

}

int Food(struct Game *p)
{
	int ok = 0;
	int tries = 0;
	while (!ok && tries < 100)
	{
		p->food_x = rand() % (p->gridnum_x + 1);							//生成新食物位置不能与蛇身重合
		p->food_y = rand() % (p->gridnum_y + 1);
		ok = 1;

		for (int a = 0;a < p->body_length; a++)
		{
			if (p->body_x[(a + p->oldest) % 2500] == p->food_x && p->body_y[(a + p->oldest) % 2500] == p->food_y)
			{
				ok = 0;
				break;
			}
		}
		tries++;
	}

	if (ok)
	{
		return 1;
	}
	else {
		return 0;
	}
}