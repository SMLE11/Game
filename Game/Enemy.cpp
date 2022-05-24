#include "Enemy.h"
extern void putimagePng(int img_x, int img_y, IMAGE* pSrcImg);

void Enemy::init()
{
	if (type == 0)
	{
		loadimage(&im_show, _T(".\\image\\enemy1.png"));
		v_x = 0;
	}
	else
	{
		loadimage(&im_show, _T(".\\image\\enemy2.png"));
		v_x = 10;
		
	}
		height = im_show.getheight();
		width = im_show.getwidth();
		setXY(0, 0);
		alive = true;
		step = 200;
}

void Enemy::draw()
{
	putimagePng(loc_left, loc_top, &im_show);
}
void Enemy::setXY(float x, float y)
{
	loc_left = x;
	loc_right = x + width;
	loc_bottom = y;
	loc_top = loc_bottom - height;
}
void Enemy::move()
{
	if (step>0)
	{
		setXY(loc_left + v_x, loc_bottom);
		step--;
	}
	else
	{
		alive = 0;
	}
}

