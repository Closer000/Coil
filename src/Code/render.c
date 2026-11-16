#include<raylib.h>
#include"game.h"

static const Color color_grid = { 82,82,82,255 };			//网格颜色（测试用）

void TestGrid_render(const Game*g)
{
	if (g->test)
	{
		for (int i = 0;i <= g->gridnum_x + 1; i++)		//绘制测试用网格
		{
			DrawLine(i * g->gridLength, 0, i * g->gridLength, GetScreenHeight(), color_grid);
			DrawLine(0, i * g->gridLength, GetScreenWidth(), i * g->gridLength, color_grid);
		}
	}
}

void Body_render(const Game* g)
{
	for (int j = 0; j < g->body_length; j++)													 //绘制蛇身
	{
		DrawRectangle((int)(g->body_x[(g->oldest + j) % 2500] * g->gridLength), (int)(g->body_y[(g->oldest + j) % 2500] * g->gridLength), g->gridLength, g->gridLength, WHITE);
	}
}

void Food_render(const Game* g)
{
	DrawCircle(g->food_x * g->gridLength + g->gridLength / 2, g->food_y * g->gridLength + g->gridLength / 2, (float)(g->gridLength / 5), YELLOW);//绘制食物
}

void Score_render(const Game* g)
{
	DrawText(TextFormat("Score: %d / %d", g->score, g->target), 10, 10, 30, YELLOW); //显示分数
}