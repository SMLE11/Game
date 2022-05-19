#pragma once
#include <graphics.h>
class Enemy
{
public:
	IMAGE im_show;
	float height, width;
	float loc_left, loc_right, loc_top, loc_bottom;
	float v_x;
	bool alive;
	int type;
	int step;
public:
	void draw();
	void setXY(float x, float y);
	void init();
	void move();
	Enemy(int t)
	{
		type = t;
	}
};

