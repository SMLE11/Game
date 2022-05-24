#include "Scene.h"
#include "publicHeader.h"
#include <ctime>
extern int getRand(int min, int max);
extern void putimagePng(int img_x, int img_y, IMAGE* pSrcImg);


void Scene::init()
{
	create_cd = 10;
	lands.clear();
	enemys.clear();
	float last_x = WIDTH / 2, last_y = HEIGHT*2 / 3;
	float px, py;
	loadimage(&bk, _T(".\\image\\background.jpg"));
	loadimage(&zdz, _T(".\\image\\zdzbig.png"));
	loadimage(&blood, _T(".\\image\\blood.jpg"));
	Land L_first;
	L_first.init();
	L_first.setXY(last_x, last_y);
	lands.push_back(L_first);
	srand(time(0));
	
	for (int i = 0; i < 30+2*(Level); i++)
	{
		Land L;
		L.init();
		int num = getRand(0, level);
		if (num)
		{
			px = getRand(0, L.width*(0.7+0.35*level)) + L.width;
			py = getRand(-L.height*(1.2+0.25*level), L.height* (1.2 + 0.25 * level));
		}
		else
		{
			px = L.width;
			py = 0;
		}
		last_x = last_x + px;
		last_y = last_y - py;
		L.setXY(last_x, last_y);
		lands.push_back(L);
		int num_enemy = getRand(0, 10-level);
		if (num_enemy == 0)
		{
			Enemy enemy(0);
			enemy.init();
			enemy.setXY(last_x + L.width / 2, last_y - L.height);
			enemys.push_back(enemy);
		}

	}
	Land land_last;
	loadimage(&land_last.im_show, _T(".\\image\\patient.png"));
	land_last.width = land_last.im_show.getwidth();
	land_last.height = land_last.im_show.getheight();
	land_last.setXY(last_x , last_y-lands[0].height);
	lands.push_back(land_last);

}
void Scene::draw()
{
	putimage(0, 0, &bk);
	for (int i = 0; i < lands.size(); i++)
	{
		lands[i].draw();
	}
	for (int i = 0; i < enemys.size(); i++)
	{
		if(enemys[i].alive)
			enemys[i].draw();
	}
}
void Scene::change_loc_x(float x)
{
	for (int i = 0; i < lands.size(); i++)
	{
		lands[i].setXY(lands[i].loc_left +x, lands[i].loc_bottom);
	}
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i].setXY(enemys[i].loc_left + x, enemys[i].loc_bottom);
	}
}
void Scene::change_loc_y(float y)
{
	for (int i = 0; i < lands.size(); i++)
	{
		lands[i].setXY(lands[i].loc_left , lands[i].loc_bottom+y);
	}
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i].setXY(enemys[i].loc_left, enemys[i].loc_bottom + y);
	}
}
void Scene::start_frame()
{
	loadimage(&bk, _T(".\\image\\background.jpg"));
	level = 0;
	Level = 0;
	putimage(0, 0, &bk);
	IMAGE im_title, im_press, im_s1, im_s2,im_author;
	loadimage(&im_title, _T(".\\image\\title.png"));
	loadimage(&im_press, _T(".\\image\\press_start.png"));
	loadimage(&im_s1, _T(".\\image\\s1.png"));
	loadimage(&im_s2, _T(".\\image\\s2.png"));
	loadimage(&im_author, _T(".\\image\\author.png"));
	putimagePng(WIDTH / 5+50, HEIGHT / 5, &im_title);
	putimagePng(WIDTH / 5+100, HEIGHT / 5+200, &im_press);
	putimagePng(WIDTH*3/6+120,0, &im_author);
	_getch();
	putimage(0, 0, &bk);
	putimagePng(WIDTH / 6 , HEIGHT / 6+30, &im_s1);
	putimagePng(WIDTH / 6 , HEIGHT / 6+200, &im_s2);
	Sleep(1000);
	_getch();

}
void Scene::next_level()
{
	level++;
	Level++;
	if (level > 5)
		level = 5;
	init();
}
void Scene::update()

{
	if (create_cd==0)
	{
		create_cd = 10;
		int num = getRand(0, 60-10*level);
		if (num == 0)
		{
			Enemy fly(1);
			fly.init();
			int f = getRand(0, 1);
			int h = getRand(0, HEIGHT);
			if (f)
			{
				fly.setXY(WIDTH, h);
				fly.v_x = -(10+level*2);
			}
			else
			{
				fly.setXY(0 - fly.width, h);
				fly.v_x = 10 + level * 3;
			}
			enemys.push_back(fly);
		}
	}
	else
	{
		create_cd--;
	}
	for (int i = 0; i < enemys.size(); i++)
	{
		if(enemys[i].type==1)
			enemys[i].move();
	}
	
}
