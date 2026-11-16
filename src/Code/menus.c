#include<raylib.h>
#include"game.h"
#include"render.h"
#include"textbutton.h"
#include"restart.h"

//所需文本
static const char* gameover = "Game Over!";	
static const char* start = "Press Any Key to Start";
static const char* rest = "Press R to Restart";
static const char* win = "Win !";
static const char* title = "Coil";
static const char* options = "Options";
static const char* grid = "Grid On";
static int text_w;
static int text_x;
static int text_y;
Color off = { 255,255,255,255 };		//未选取的按钮颜色
Color on = { 253,249,0,255 };			//被选取的按钮颜色

void Beforestart(struct Game* g)
{
	switch (g->menu)
	{
	case 0:
		text_w = MeasureText(title, 300);
		text_x = GetScreenWidth() / 2 - text_w / 2;
		text_y = 100;
		DrawText(title, text_x, text_y, 300, WHITE);

		if (TextButton("Play", GetScreenWidth() / 2, GetScreenHeight() / 2, 50, off, on))
		{
			g->menu = 1;
		}
		break;
	case 1:

		TestGrid_render(g);
		text_w = MeasureText(options, 200);
		text_x = GetScreenWidth() / 2 - text_w / 2;
		text_y = 200;
		DrawText(options, text_x, text_y, 200, WHITE);

		if (TextButton("Grid On/Off", GetScreenWidth() / 2, GetScreenHeight() - 50, 50, off, on))
		{
			g->test = !g->test;
			g->menu = 1;
		}
		if (TextButton("Back", GetScreenWidth() / 2, 50, 50, off, on))
		{
			g->menu = 0;
		}
		if (TextButton("Easy", GetScreenWidth() / 2, text_y + 275, 50, off, on))
		{
			g->target = 20;
			g->menu = 2;
		}
		if (TextButton("Normal", GetScreenWidth() / 2, text_y + 350, 50, off, on))
		{
			g->target = 50;
			g->menu = 2;
		}
		if (TextButton("Hard", GetScreenWidth() / 2, text_y + 425, 50, off, on))
		{
			g->target = 100;
			g->menu = 2;
		}
		break;
	case 2:
		text_w = MeasureText(start, 50);
		text_x = GetScreenWidth() / 2 - text_w / 2;
		text_y = GetScreenHeight() / 2 - 50 / 2;
		DrawText(start, text_x, text_y, 50, WHITE);

		if (TextButton("Back", GetScreenWidth() / 2, 50, 50, off, on))
		{
			g->menu = 1;
		}

		if (GetKeyPressed())
		{
			g->game = 1;
		}
		break;
	}
}

void Defeae(struct Game* g)		//失败情况
{
	text_w = MeasureText(gameover, 100);
	text_x = GetScreenWidth() / 2 - text_w / 2;
	text_y = GetScreenHeight() / 2 - 100 / 2;
	DrawText(gameover, text_x, text_y, 100, RED);

	text_w = MeasureText(rest, 50);
	text_x = GetScreenWidth() / 2 - text_w / 2;
	text_y = (GetScreenHeight() / 2 - 50 / 2) + 100;
	DrawText(rest, text_x, text_y, 50, WHITE);

	if (IsKeyDown(KEY_R))
	{
		Restart(g);
		g->menu = 2;
	}
}

void Win(struct Game* g)		//胜利情况
{
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
		Restart(g);
		g->menu = 2;
	}
}