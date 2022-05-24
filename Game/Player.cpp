#include "Player.h"
extern void putimagePng(int img_x, int img_y, IMAGE* pSrcImg);
void Player::getImage()
{
	loadimage(&im_attack_right, _T(".\\image\\attack_right.png"));
	loadimage(&im_attack_left, _T(".\\image\\attack_left.png"));
	loadimage(&im_stand_right, _T(".\\image\\stand_right.png"));
	loadimage(&im_stand_left, _T(".\\image\\stand_left.png"));
}
void Player::updateXY(float x, float y)
{
	loc_x = x;
	loc_y = y;
}
void Player::draw()
{
	putimagePng(loc_x,loc_y-height,&im_show);
	for (int i = 0; i < 30; i++)
	{
		if (bullet[i].flag)
		{
			bullet[i].draw();
			bullet[i].move();
		}
	}
}
void Player::runRight(Scene& sc)
{
	bool is_collide = false;
	float loc_right = loc_x + width;
	float loc_top = loc_y - height;
	
	
	for (int i = 0; i < sc.lands.size(); i++)
	{
			if ((sc.lands[i].loc_top>loc_top&& sc.lands[i].loc_top<loc_y)||(sc.lands[i].loc_bottom<loc_y&& sc.lands[i].loc_bottom>=loc_top))
			{
				if (loc_right + v_x >= sc.lands[i].loc_left && loc_right <= sc.lands[i].loc_left)
				{
					loc_right = sc.lands[i].loc_left;
					loc_x = loc_right - width;
					is_collide = true;
					if (i == sc.lands.size() - 1)
					{
						loc_y = sc.lands[sc.lands.size() - 1].loc_bottom;
						next_level(sc);
						return;
					}
					break;
				}

			}
	}
	int landSize = sc.lands.size(); // 场景中地面的个数

	
	if (!is_collide)
	{
		if (walk_music_cd == 0)
		{
			PlayMusicOnce(_T(".\\bgm\\walk.mp3"));
			walk_music_cd = 20;
		}
		else
		{
			walk_music_cd--;
		}
		if (loc_right + v_x > WIDTH * 2 / 3)
		{
			loc_x = WIDTH * 2 / 3 - width;
			sc.change_loc_x(-v_x);
		}
		else
			loc_x += v_x;
	}
		
	ps = stand_right;
	im_show = im_stand_right;
	
}
void Player::runLeft(Scene& sc)
{
	bool is_collide = false;
	float loc_top = loc_y - height;
	
	
	for (int i = 0; i < sc.lands.size(); i++)
		{
			if ((sc.lands[i].loc_top > loc_top && sc.lands[i].loc_top < loc_y) || (sc.lands[i].loc_bottom < loc_y && sc.lands[i].loc_bottom > loc_top))
			{
				if (loc_x - v_x <= sc.lands[i].loc_right && loc_x >= sc.lands[i].loc_right)
				{
					loc_x = sc.lands[i].loc_right;
					is_collide = true;
					break;
				}

			}
	}

	if (!is_collide)
	{
		if (walk_music_cd == 0)
		{
			PlayMusicOnce(_T(".\\bgm\\walk.mp3"));
			walk_music_cd = 20;
		}
		else
		{
			walk_music_cd--;
		}
		if (loc_x - v_x < WIDTH / 3)
		{
			loc_x = WIDTH / 3;
			sc.change_loc_x(v_x);
		}
		else
			loc_x -= v_x;
	}
	ps = stand_left;
	im_show = im_stand_left;
}
void Player::jump()
{
	if (isLand)
	{
		PlayMusicOnce(_T(".\\bgm\\jump.mp3"));
		v_y = -20;
	}
}
void Player::attack()
{
	attack_animId = 10;
	if (ps == stand_left)
	{
		ps = attack_left;
		im_show = im_attack_left;
	}
	else if (ps == stand_right)
	{
		ps = attack_right;
		im_show = im_attack_right;
	}
	creat_bullet();
}
void Player::stand_still()
{
	if (ps == stand_right || ps == attack_right)
	{
		ps = stand_right;
		im_show = im_stand_right;
	}
	if (ps == stand_left || ps == attack_left)
	{
		ps = stand_left;
		im_show = im_stand_left;
	}
}
void Player::updateAndCheckY(Scene& sc)
{
	isLand = false;
	for (int i = 0; i < sc.lands.size(); i++)
	{
		isOnLand(sc.lands[i]);
	}
	if(!isLand)
	{
		if (loc_Y + v_y < HEIGHT+200)
		{
			sc.change_loc_y(-v_y);
			loc_Y += v_y;
		}
		else
		{
			restart(sc);
		}
	}
	


	if (!isLand)
	{
		v_y += gravity;
	}
	else
	{
		v_y = 0;
	}

	

}
void Player::init()
{
	
	getImage();
	v_x = 10;
	v_y = 0;
	gravity = 2;
	updateXY(WIDTH / 2, HEIGHT/2-10);
	ps = stand_right;
	im_show = im_stand_right;
	height = im_show.getheight();
	width = im_show.getwidth();
	isLand = true;
	attack_animId = 0;
	loc_Y = loc_y;
	for (int i = 0; i < 30; i++)
	{
		bullet[i].init();
	}
	cd = 0;
	walk_music_cd = 0;
	//TCHAR s[10];
	//_stprintf_s(s, _T("%d %d"), (int)loc_x, (int)height);		// 高版本 VC 推荐使用 _stprintf_s 函数
	//outtextxy(0, 60, s);
}
void Player::control_detect(Scene& sc)
{
	
	if (attack_animId != 0)
	{
		attack_animId--;
	}
	else
	{
		stand_still();
		if (_kbhit())
		{
			if (GetAsyncKeyState('D'))
			{
				runRight(sc);

			}
			if (GetAsyncKeyState('A'))
			{
				runLeft(sc);
			}
			if (GetAsyncKeyState('W'))
			{
				jump();
			}
			if (GetAsyncKeyState('J'))
			{
				attack();
			}
		}
	}
	
}
void Player::isOnLand(Land& land)
{
	float loc_left = loc_x;
	float loc_right = loc_left + width;
	float loc_top = loc_y - height;
	if (loc_right > land.loc_left && loc_left < land.loc_right)
	{
		if (v_y>0&&loc_y + v_y > land.loc_top&&loc_y<=land.loc_top)
		{
			v_y = land.loc_top-loc_y;
			isLand = true;
		}
		if (v_y < 0&& loc_top+ v_y<=land.loc_bottom&&loc_top>= land.loc_bottom)
		{
			v_y =  land.loc_bottom-loc_top;
		}
	}
}
void Player::next_level(Scene& sc)
{
	PlayMusicOnce(_T(".\\bgm\\win.mp3"));
	Sleep(2000);
	init();
	sc.next_level();
}
void Player::creat_bullet()
{
	static int idx = 0;
	while (bullet[idx].flag)
	{
		idx++;
		idx %= 30;
	}
	if (cd == 0)
	{
		bullet[idx].flag = true;
		cd = 10;
		PlayMusicOnce(_T(".\\bgm\\attack.mp3"));
		if (ps == attack_right||ps==stand_right)
		{
			bullet[idx].set_direction(0);
			bullet[idx].setXY(loc_x + width, loc_y - height / 2);
		}
		else if (ps == attack_left|| ps == stand_left)
		{
			bullet[idx].set_direction(1);
			bullet[idx].setXY(loc_x -bullet[idx].width, loc_y - height / 2);
		}

	}
	
	
	
}
void Player::update(Scene& sc)
{
	updateAndCheckY(sc);
	CollideEnemy_detect(sc);
	if (cd > 0)
	{
		cd--;
	}
	for (int i = 0; i < 30; i++)
	{
		if (bullet[i].flag)
		{
			for (int j = 0; j < sc.enemys.size(); j++)
			{
				bullet[i].CollideEnemy_detect(sc.enemys[j]);
			}
		}
	}
	if (loc_x + width > sc.lands[sc.lands.size() - 1].loc_left && loc_y - height < sc.lands[sc.lands.size() - 1].loc_top)
		next_level(sc);
}
void Player::restart(Scene& sc)
{
	draw();
	sc.draw();
	PlayMusicOnce(_T(".\\bgm\\player_death.mp3"));
	Sleep(2000);
	init();
	sc.init();
}
int Player::isCollideEnemy(Enemy& enemy) // 判断角色是否和敌人碰撞，如果是返回1，否则返回0
{
	if (!enemy.alive)
		return 0;
	float x_center = enemy.loc_left + enemy.width / 2;
	float y_center = enemy.loc_bottom - enemy.height / 2;
	if (x_center<loc_x+width&&x_center>loc_x&&
		y_center<loc_y&&y_center>loc_y-height)
		return 1;
	else
		return 0;
}
void Player::CollideEnemy_detect(Scene& sc)
{
	for (int i = 0; i < sc.enemys.size(); i++)
	{

		if (sc.enemys[i].alive&&isCollideEnemy(sc.enemys[i]))
		{
			draw();
			restart(sc);
			return;
		}

	}
}

