#include<Raylib.h>

int TextButton(const char* text, int mid_x, int mid_y, int fontsize, Color color1, Color color2)		//纯文本按钮
{
	int in;
	int textwidth = MeasureText(text, fontsize);
	Rectangle t = {
		(float)(mid_x - (textwidth + 20) / 2),
		(float)(mid_y - (fontsize + 10) / 2),
		(float)(textwidth + 20),
		(float)(fontsize + 10)
	};
	DrawText(text, mid_x - textwidth / 2, mid_y - fontsize / 2, fontsize, color1);
	in = CheckCollisionPointRec(GetMousePosition(), t);
	if (in)
	{
		DrawText(text, mid_x - textwidth / 2, mid_y - fontsize / 2, fontsize, color2);
	}
	if (in && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		return 1;
	}
	else {
		return 0;
	}
}