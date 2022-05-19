#pragma once
#include "publicHeader.h"
class Land
{
public:
	IMAGE im_show;
	float height, width;
	float loc_left, loc_right, loc_top, loc_bottom;
public:
	void init();
	void draw();
	void setXY(float x, float y);
};

