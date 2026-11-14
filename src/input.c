#include<raylib.h>
#include"game.h"

//判定移动方向：(1,0)为向右一格，(-1,0)为向左一格，(0,-1)为向上一格，(0,1)向下一格
void Direction(struct Game* g)
{
	if (IsKeyDown(KEY_W))
	{
		g->pre_dx = 0;
		g->pre_dy = -1;
	}
	else if (IsKeyDown(KEY_S))
	{
		g->pre_dx = 0;
		g->pre_dy = 1;
	}
	else if (IsKeyDown(KEY_A))
	{
		g->pre_dx = -1;
		g->pre_dy = 0;
	}
	else if (IsKeyDown(KEY_D))
	{
		g->pre_dx = 1;
		g->pre_dy = 0;
	}
	
	//禁止原地反向移动
	if (g->pre_dx != -g->last_dx || g->pre_dy != -g->last_dy)
	{
		g->dx = g->pre_dx;
		g->dy = g->pre_dy;
	}
}