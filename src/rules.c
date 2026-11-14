#include"game.h"
#include<raylib.h>

 //蛇头不能撞身体
void Selfcrash(struct Game* g, int add)
{
	for (int c = 0; c < g->body_length - 1; c++)			
	{
		if (g->body_x[add] == g->body_x[(c + g->oldest) % 2500] && g->body_y[add] == g->body_y[(c + g->oldest) % 2500])
		{
			g->game = -1;
			break;
		}
	}
}

//钳制dt限制每帧位移
void Clamp(struct Game* g)
{
	g->dt = GetFrameTime();	//获取时间的帧改变量									 
	if (g->dt >= 0.20)												 
	{
		g->dt = 0.20;
	}
	else if (g->dt <= 0)
	{
		g->dt = 0;
	}
}