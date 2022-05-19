#include "Land.h"
extern void putimagePng(int img_x, int img_y, IMAGE* pSrcImg);
void Land::init()
{
	loadimage(&im_show, _T(".\\image\\land.png"));
	height = im_show.getheight();
	width = im_show.getwidth();
	setXY(0, 0);
}
void Land::draw()
{
	putimagePng(loc_left,loc_top,&im_show);
}
void Land::setXY(float x, float y)
{
	loc_left = x;
	loc_right = x + width;
	loc_bottom = y;
	loc_top = loc_bottom - height;
}
