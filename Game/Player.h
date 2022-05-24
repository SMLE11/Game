#pragma once
#include "publicHeader.h"
#include "Land.h"
#include "Scene.h"
#include "Bullet.h"
#include "Enemy.h"
extern void PlayMusicOnce(TCHAR fileName[80]);
extern void _PlayMusicOnce(TCHAR fileName[80]);
enum PlayerStates
{
	stand_right, stand_left,attack_right,attack_left
};
class Player
{
public:
	float height, width;
	float loc_x, loc_y,loc_Y;
	float v_x,v_y;
	float gravity;
	IMAGE im_show,im_attack_right,im_attack_left,im_stand_right,im_stand_left;
	PlayerStates ps;
	bool isLand;
	int attack_animId;
	int cd;
	int walk_music_cd;
	Bullet bullet[30];

public:

	void getImage();
	void runRight(Scene& sc);
	void runLeft(Scene& sc);
	void jump();
	void updateXY(float x, float y);
	void draw();
	void updateAndCheckY(Scene& sc);
	void init();
	void control_detect(Scene& sc);
	void attack();
	void stand_still();
	void isOnLand(Land& land);
	void next_level(Scene& sc);
	void creat_bullet();
	void update(Scene& sc);
	void restart(Scene& sc);
	int isCollideEnemy(Enemy& enemy);
	void CollideEnemy_detect(Scene& sc);
};
