#pragma once

typedef struct Game
{
	int x, y;								//定义x,y作为计算位置的临时变量
	double left;							//消耗的时间
	double dt;								//上一帧耗时
	int dx, dy;								//生效移动方向及移动量
	int pre_dx, pre_dy;						//下一移动方向及移动量
	int last_dx, last_dy;					//上一移动方向及移动量
	int body_x[2500], body_y[2500];         //蛇身位置
	int body_length;						//蛇身长度
	int oldest;								//最旧下标
	int food_x, food_y;						//食物的位置
	int game;								//游戏状态
	int menu;								//游戏菜单
	int gridnum_x, gridnum_y;				//换算为格子坐标后的最大索引
	int gridLength;							//格子边长
	int score;								//得分
	int test;								//网格
}Game;