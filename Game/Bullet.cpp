#include "Bullet.h"
extern void putimagePng(int img_x, int img_y, IMAGE* pSrcImg);
void Bullet::init()
{
	loadimage(&im_left, _T(".\\image\\bullet_left.png"));
	loadimage(&im_right, _T(".\\image\\bullet_right.png"));
	im_show = im_right;
	height = im_show.getheight();
	width = im_show.getwidth();
	v_x = 30;
	flag = false;
	step = 0;
}
void Bullet::draw()
{
	putimagePng(loc_left, loc_top, &im_show);
}
void Bullet::setXY(float x, float y)
{
	loc_left = x;
	loc_right = x + width;
	loc_bottom = y;
	loc_top = loc_bottom - height;
}
void Bullet::move()
{
	if (step < 20)
	{
		setXY(loc_left + v_x, loc_bottom);
		step++;
	}
	else
	{
		step = 0;
		flag = false;
	}
	
}
void Bullet::set_direction(int F)
{
	step = 0;
	if (F == 0)
	{
		im_show = im_right;
		v_x = 30;
	}
	else
	{
		im_show = im_left;
		v_x = -30;
	}
}



void Bullet::CollideEnemy_detect(Enemy& enemy)
{
	if (flag == false||enemy.alive==false)
		return;
	float x_center = loc_left + width / 2;
	float y_center = loc_bottom - height / 2;
	if (x_center<enemy.loc_left + width && x_center>enemy.loc_left &&
		y_center<enemy.loc_bottom && y_center>enemy.loc_bottom - enemy.height)
	{
		enemy.alive = false;
		flag = false;
		step = 0;
	}
}
