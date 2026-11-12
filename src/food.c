#include<stdlib.h>
#include"game.h"

int Food_swapn(struct Game* p)
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