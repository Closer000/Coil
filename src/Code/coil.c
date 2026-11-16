#include<raylib.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"game.h"
#include"food.h"
#include"restart.h"
#include"rules.h"
#include"textbutton.h"
#include"render.h"
#include"input.h"
#include"menus.h"

Game G;

int main()
{
	InitWindow(1000, 1000, "snake");
	Image Icon = LoadImage("SnakeIcon.png");
	SetWindowIcon(Icon);
	UnloadImage(Icon);
	SetTargetFPS(60);
						
	srand((unsigned int)time(0));

	Restart(&G);
	G.menu = 0;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		switch (G.game)
		{
		case 0:
			Beforestart(&G);
			break;
		case 1:
			Clamp(&G);
			Direction(&G);
			Move(&G);
			TestGrid_render(&G); 
			Body_render(&G);
			Food_render(&G);
			Score_render(&G);		
			break;
		case -1:
			Defeae(&G);
			break;
		case 2:
			Win(&G);
			break;
		}
		EndDrawing();
	}
	CloseWindow();

	return 0;
}




