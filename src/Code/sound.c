#include<raylib.h>
#include"sound.h"

Sound eat;
Sound victory;
Sound die;
Sound hover;
Sound click;

void Init_sound(void)
{
	eat = LoadSound("eat.wav");
	victory = LoadSound("win.wav");
	die = LoadSound("die.wav");
	hover = LoadSound("hover.wav");
	click = LoadSound("click.wav");
}

void Close_sound(void)
{
	UnloadSound(eat);
	UnloadSound(victory);
	UnloadSound(die);
	UnloadSound(hover);
	UnloadSound(click);
}
