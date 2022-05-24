// Game.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <EasyXPng.h>
#include <iostream>
#include <conio.h>
#include "publicHeader.h"
#include "Player.h"
#include "Scene.h"
#include "Land.h"
using namespace std;
Player player;
Scene sc;
void StartUp();
void Show();
void UpdateWithInput();
void UpdateWithoutInput();
void PlayMusicOnce(TCHAR fileName[80]);
int getRand(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}
int main()
{
	StartUp();

	while (true)
	{
		Show();
		UpdateWithInput();
		UpdateWithoutInput();
		Sleep(20);

	}
}
void StartUp()
{
	mciSendString(_T("open .\\bgm\\bgm_.mp3 alias bkmusic"), NULL, 0, NULL);//打开背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);  // 循环播放
	initgraph(WIDTH, HEIGHT);	
	sc.start_frame();
	sc.init();
	player.init();
	BeginBatchDraw();
}
void Show()
{
	sc.draw();
	player.draw();
	TCHAR s[20]; // 字符串
	setbkmode(TRANSPARENT); // 文字透明显示
	_stprintf_s(s, _T("第 %d 关"), (int)sc.Level+1); // 生成文字字符串
	settextcolor(RGB(255, 255, 255));  // 设置文字颜色
	settextstyle(30, 0, _T("黑体")); // 设置文字大小、字体
	outtextxy(WIDTH * 0.45, 30, s); // 输出文字
	//TCHAR s[30];
	//_stprintf_s(s, _T("%d %d"), (int)player.loc_y, (int)sc.enemys[0].loc_top);		// 高版本 VC 推荐使用 _stprintf_s 函数
	//outtextxy(10, 60, s);
	FlushBatchDraw();
	
}
void UpdateWithInput()
{
	player.control_detect(sc);
}
void UpdateWithoutInput()
{
	sc.update();
	player.update(sc);
}
void PlayMusicOnce(TCHAR fileName[80]) // 播放一次音乐函数
{
	TCHAR cmdString1[50];
	_stprintf_s(cmdString1, _T("open %s alias tmpmusic"), fileName); // 生成命令字符串
	mciSendString(_T("close tmpmusic"), NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString(cmdString1, NULL, 0, NULL); // 打开音乐
	mciSendString(_T("play tmpmusic"), NULL, 0, NULL); // 仅播放一次
}




// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
