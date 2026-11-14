#include<raylib.h>
#include"game.h"
#include"food.h"


 //蛇头不能撞身体
void Selfcrash(struct Game* g)
{
	for (int c = 0; c < g->body_length - 1; c++)			
	{
		if (g->body_x[g->add] == g->body_x[(c + g->oldest) % 2500] && g->body_y[g->add] == g->body_y[(c + g->oldest) % 2500])
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

void Move(struct Game* g)
{
	g->left += g->dt;
	for (int i = 0; i < 2; i++)         //移动
	{
		if (g->left >= g->step)
		{
			int next_x = g->x + g->dx;
			int next_y = g->y + g->dy;
			if (next_x <= g->gridnum_x && next_x >= 0 && next_y <= g->gridnum_y && next_y >= 0)//判断越界
			{
				g->last_dx = g->dx;
				g->last_dy = g->dy;
				g->add = (g->oldest + g->body_length) % 2500;
				g->x = next_x;
				g->y = next_y;
				g->body_x[g->add] = g->x;
				g->body_y[g->add] = g->y;
				g->body_length++;

				if (g->x != g->food_x || g->y != g->food_y)
				{
					g->oldest = (g->oldest + 1) % 2500;
					g->body_length--;
				}
				else {
					Food_swapn(g);
					g->score++;
					if (g->score >= g->target)
					{
						g->game = 2;
					}
				}
				Selfcrash(g);
			}
			else {
				g->game = -1;
				break;
			}
			g->left = g->left - g->step;
		}
	}
}