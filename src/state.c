#include<raylib.h>
#include"game.h"
#include"food.h"

void Restart(struct Game* p)
{
	p->gridLength = 20;
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

	Food_swapn(p);

	p->game = 0;

	p->score = 0;
}

void Selfcrash(struct Game* g, int add)
{
	for (int c = 0; c < g->body_length - 1; c++)			//蛇头不能撞身体
	{
		if (g->body_x[add] == g->body_x[(c + g->oldest) % 2500] && g->body_y[add] == g->body_y[(c + g->oldest) % 2500])
		{
			g->game = -1;
			break;
		}
	}
}