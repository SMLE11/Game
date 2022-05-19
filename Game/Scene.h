#pragma once
#include <graphics.h>
#include "publicHeader.h"
#include "Land.h"
#include <vector>
#include "Enemy.h"
extern void PlayMusicOnce(TCHAR fileName[80]);

using namespace std;
class Player;
class Scene
{
public:
	IMAGE bk, zdz, blood;
	vector<Land> lands;
	vector<Enemy> enemys;
	vector<Enemy> flys;
	int level,Level;
	int create_cd;
	
	
public:
	void init();
	void draw();
	void change_loc_x(float x);
	void change_loc_y(float y);
	void start_frame();
	void next_level();
	void update();
};

