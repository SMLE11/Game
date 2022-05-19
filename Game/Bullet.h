#pragma once
#include "publicHeader.h"
#include "Enemy.h"
class Bullet
{
public:
	IMAGE im_show,im_right,im_left;
	float height, width;
	float loc_left, loc_right, loc_top, loc_bottom;
	float v_x;
	bool flag;
	int step;

public:
	void draw();
	void setXY(float x, float y);
	void init();
	void move();
	void set_direction(int F);
	void CollideEnemy_detect(Enemy& enemy);
};

