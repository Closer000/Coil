#include"game.h"

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