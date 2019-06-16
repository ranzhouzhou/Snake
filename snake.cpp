// snake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <sstream>
#include <fstream>
using namespace std;

struct coor 
{
	int x;
	int y;
};
enum DIRECTION 
{
	goup,
	godown,
	goleft,
	goright
};
struct SNAKE 
{
	int n;
	coor scoor[100];
	enum DIRECTION direction;
}snake;
struct FOOD 
{
	coor fcoor;
	int flag;
}food;
struct WALL
{
	int sum;
	coor wcoor[100];
}wall;
struct SCORELIST
{
	int simple[10];
	int difficult[10];
}scorelist;

int score;
int againflag;
int level;

IMAGE snakeup;
IMAGE snakedown;
IMAGE snakeleft;
IMAGE snakeright;
IMAGE snakeupeat;
IMAGE snakedowneat;
IMAGE snakelefteat;
IMAGE snakerighteat;
IMAGE snakebody;
IMAGE foodimage;
IMAGE wallimage;
IMAGE background;

int GetSpeed(int i) 
{
	if (i <= 2)
	{
		return level * 100;
	}
	if (i <= 3)
	{
		return level * 125;
	}
	return level * 150;
}
void GetWall(int l)
{
	if (l == 1)
	{
		wall.sum = 36;
		for (int i = 0, j = 0; i < 9; i++)
		{
			wall.wcoor[i].x = j * 20;
			wall.wcoor[i].y = j * 20;
			j++;
		}
		for (int i = 9, j = 1; i < 27; i++)
		{
			wall.wcoor[i].x = 640 - j * 20;
			wall.wcoor[i].y = 400;
			j++;
		}
		for (int i = 27, j = 0; i < 36; i++)
		{
			wall.wcoor[i].x = 440;
			wall.wcoor[i].y = j * 20;
			j++;
		}
	}
	if (l == 2)
	{
		wall.sum = 64;
		for (int i = 0, j = 0; i < 9; i++)
		{
			wall.wcoor[i].x = j * 20;
			wall.wcoor[i].y = j * 20;
			j++;
		}
		for (int i = 9, j = 1; i < 27; i++)
		{
			wall.wcoor[i].x = 640 - j * 20;
			wall.wcoor[i].y = 400;
			j++;
		}
		for (int i = 27, j = 1; i < 34; i++)
		{
			wall.wcoor[i].x = 280;
			wall.wcoor[i].y = 400 - j * 20;
			j++;
		}
		for (int i = 34, j = 0; i < 46; i++)
		{
			wall.wcoor[i].x = 440;
			wall.wcoor[i].y = j * 20;
			j++;
		}
		for (int i = 46, j = 1; i < 56; i++)
		{
			wall.wcoor[i].x = 440 + j * 20;
			wall.wcoor[i].y = 220;
			j++;
		}
		for (int i = 56, j = 0; i < 64; i++)
		{
			wall.wcoor[i].x = j * 20;
			wall.wcoor[i].y = 280 + j * 20;
			j++;
		}
	}
}
void InitializeGame()
{
	initgraph(640, 480);
	setbkcolor(WHITE);
	cleardevice();
	loadimage(&snakeup, _T("resource\\snakeup.jpg"), 20, 20);
	loadimage(&snakedown, _T("resource\\snakedown.jpg"), 20, 20);
	loadimage(&snakeleft, _T("resource\\snakeleft.jpg"), 20, 20);
	loadimage(&snakeright, _T("resource\\snakeright.jpg"), 20, 20);
	loadimage(&snakeupeat, _T("resource\\snakeupeat.jpg"), 20, 20);
	loadimage(&snakedowneat, _T("resource\\snakedowneat.jpg"), 20, 20);
	loadimage(&snakelefteat, _T("resource\\snakelefteat.jpg"), 20, 20);
	loadimage(&snakerighteat, _T("resource\\snakerighteat.jpg"), 20, 20);
	loadimage(&snakebody, _T("resource\\snakebody.jpg"), 20, 20);
	loadimage(&foodimage, _T("resource\\foodimage.jpg"), 20, 20);
	loadimage(&wallimage, _T("resource\\wallimage.jpg"), 20, 20);
	loadimage(&background, _T("resource\\background.jpg"), 640,480);
	putimage(0,0, &background);
	int aa;
	aa = _getch();
	if (aa == 83 || aa == 115)
	{
		level = 1;
	}
	else if (aa == 68 || aa == 100)
	{
		level = 2;
	}
	else
	{
		level = 1;
	}
	cleardevice();
	snake.scoor[0].x = 320;
	snake.scoor[0].y = 240;
	snake.n = 2;
	snake.direction = goright;
	food.flag = 0;
	againflag = 0;
	GetWall(level);
}
void ProduceFood()
{
	while (food.flag == 0)
	{
		srand(unsigned(time(0)));
		food.fcoor.x = (rand() % 31 + 1) * 20;
		food.fcoor.y = (rand() % 23 + 1) * 20;
		food.flag = 1;
		for (int i = 0; i < wall.sum; i++)
		{
			if (food.fcoor.x == wall.wcoor[i].x && food.fcoor.y == wall.wcoor[i].y)
			{
				food.flag = 0;
				break;
			}
		}
		for (int i = 0; i < snake.n; i++)
		{
			if (food.fcoor.x == snake.scoor[i].x && food.fcoor.y == snake.scoor[i].y)
			{
				food.flag = 0;
				break;
			}
		}
	}	
}
void MoveSnake()
{
	for (int i = snake.n - 1; i > 0; i--) 
	{
		snake.scoor[i].x = snake.scoor[i - 1].x;
		snake.scoor[i].y = snake.scoor[i - 1].y;
	}
	switch (snake.direction)
	{
	case goup:
		snake.scoor[0].y -= 20;
		break;
	case godown:
		snake.scoor[0].y += 20;
		break;
	case goleft:
		snake.scoor[0].x -= 20;
		break;
	case goright:
		snake.scoor[0].x += 20;
		break;
	}
	for (int i = 0; i < snake.n; i++)
	{
		if (snake.scoor[i].x < 0)
		{
			snake.scoor[i].x += 640;
			break;
		}
		if (snake.scoor[i].x >= 640)
		{
			snake.scoor[i].x -= 640;
			break;
		}
		if (snake.scoor[i].y < 0)
		{
			snake.scoor[i].y += 480;
			break;
		}
		if (snake.scoor[i].y >= 480)
		{
			snake.scoor[i].y -= 480;
			break;
		}
	}
	switch (snake.direction)
	{
	case goup:
		putimage(snake.scoor[0].x, snake.scoor[0].y,&snakeup);
		break;
	case godown:
		putimage(snake.scoor[0].x, snake.scoor[0].y, &snakedown);
		break;
	case goleft:
		putimage(snake.scoor[0].x, snake.scoor[0].y, &snakeleft);
		break;
	case goright:
		putimage(snake.scoor[0].x, snake.scoor[0].y, &snakeright);
		break;
	}
	for (int i = snake.n - 1; i > 0; i--)
	{
		putimage(snake.scoor[i].x, snake.scoor[i].y, &snakebody);
	}
}
void EatFood()
{
	if (snake.scoor[0].x == food.fcoor.x && snake.scoor[0].y == food.fcoor.y)
	{
		snake.n++;
		food.flag = 0;
	}
}
void GetDirection()
{
	switch (_getch())
	{ 
	case 'w':
	case 'W':
	case 72:
		if (snake.direction != godown)
		{
			snake.direction = goup;
		}
		break;
	case 's':
	case 'S':
	case 80:
		if (snake.direction != goup)
		{
			snake.direction = godown;
		}
		break;
	case 'a':
	case 'A':
	case 75:
		if (snake.direction != goright)
		{
			snake.direction = goleft;
		}
		break;
	case 'd':
	case 'D':
	case 77:
		if (snake.direction != goleft)
		{
			snake.direction = goright;
		}
		break;
	}
}
void GetScorelist(int l)
{
	if (l == 1)
	{
		ifstream infile;
		infile.open("resource\\simplescore.txt");
		int j = 0;
		while (!infile.eof() && j < 10)
		{
			string str;
			getline(infile, str);
			stringstream ss;
			ss << str;
			ss >> scorelist.simple[j];
			j++;
		}
		infile.close();
		for (int i = 0; i < 10; i++)
		{
			if (score >= scorelist.simple[i])
			{
				for (int j = 9; j > i; j--)
				{
					scorelist.simple[j] = scorelist.simple[j - 1];
				}
				scorelist.simple[i] = score;
				break;
			}
		}
		ofstream outfile;
		outfile.open("resource\\simplescore.txt");
		for (int i = 0; i < 10; i++)
		{
			outfile << scorelist.simple[i] << endl;
		}
		outfile.close();
	}
	else if (l == 2)
	{
		ifstream infile;
		infile.open("resource\\difficultscore.txt");
		int j = 0;
		while (!infile.eof() && j < 10)
		{
			string str;
			getline(infile, str);
			stringstream ss;
			ss << str;
			ss >> scorelist.difficult[j];
			j++;
		}
		infile.close();
		for (int i = 0; i < 10; i++)
		{
			if (score >= scorelist.difficult[i])
			{
				for (int j = 9; j > i; j--)
				{
					scorelist.difficult[j] = scorelist.difficult[j - 1];
				}
				scorelist.difficult[i] = score;
				break;
			}
		}
		ofstream outfile;
		outfile.open("resource\\difficultscore.txt");
		for (int i = 0; i < 10; i++)
		{
			outfile << scorelist.difficult[i] << endl;
		}
		outfile.close();
	}
}
void Gameover()
{
	score = snake.n - 2;
	cleardevice();
	settextcolor(BLACK);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(200, 200, _T("game over"));
	outtextxy(200, 250, _T("分数"));
	TCHAR s[3];
	_stprintf_s(s, _T("%d"), score);
	outtextxy(350, 250, s);
	outtextxy(100, 300, _T("按任意键查看排行榜"));
	_getch();
	cleardevice();
	settextstyle(20, 0, _T("黑体"));
	outtextxy(200, 20, _T("排行榜"));
	GetScorelist(level);
	if (level == 1) 
	{
		outtextxy(300, 20, _T("简单"));
		for (int i = 0; i < 10; i++)
		{
			TCHAR l[3];
			_stprintf_s(l, _T("%d"), scorelist.simple[i]);
			outtextxy(200, i * 20 + 50, l);
		}
	}
	else if (level == 2)
	{
		outtextxy(300, 20, _T("困难"));
		for (int i = 0; i < 10; i++)
		{
			TCHAR l[3];
			_stprintf_s(l, _T("%d"), scorelist.difficult[i]);
			outtextxy(200, i * 20 + 50, l);
		}
	}
	outtextxy(200, 320, _T("按任意键继续"));
	_getch();
	cleardevice();
	settextstyle(50, 0, _T("黑体"));
	outtextxy(200, 200, _T("Y重新开始"));
	outtextxy(200, 300, _T("N退出游戏"));
	int aa;
	aa = _getch();
	if (aa == 89 || aa == 121)
	{
		againflag = 1;
	}
	else if (aa == 78 || aa == 110)
	{
		exit(0);
	}
	else
	{
		againflag = 1;
	}
}
void CollisionDetection() 
{
	for (int i = 0; i < wall.sum; i++)
	{
		if (snake.scoor[0].x == wall.wcoor[i].x && snake.scoor[0].y == wall.wcoor[i].y)
		{
			Gameover();
		}

	}
	for (int i = snake.n - 1; i > 0; i--)
	{
		if (snake.scoor[0].x == snake.scoor[i].x && snake.scoor[0].y == snake.scoor[i].y)
		{
			Gameover();
		}
	}
}
int main()
{
	againflag = 1;
	while (againflag == 1) 
	{
		InitializeGame();
		while (1)
		{
			while (!_kbhit())
			{
				if (food.flag == 0)
				{
					cleardevice();
					putimage(food.fcoor.x, food.fcoor.y, &foodimage);
					for (int i = 0; i < wall.sum; i++)
					{
						putimage(wall.wcoor[i].x, wall.wcoor[i].y, &wallimage);
					}
					switch (snake.direction)
					{
					case goup:
						putimage(snake.scoor[0].x, snake.scoor[0].y, &snakeupeat);
						break;
					case godown:
						putimage(snake.scoor[0].x, snake.scoor[0].y, &snakedowneat);
						break;
					case goleft:
						putimage(snake.scoor[0].x, snake.scoor[0].y, &snakelefteat);
						break;
					case goright:
						putimage(snake.scoor[0].x, snake.scoor[0].y, &snakerighteat);
						break;
					}
					for (int i = snake.n - 2; i > 0; i--)
					{
						putimage(snake.scoor[i].x, snake.scoor[i].y, &snakebody);
					}
					Sleep(500 - GetSpeed(snake.n));
					ProduceFood();
				}
				cleardevice();
				putimage(food.fcoor.x, food.fcoor.y, &foodimage);
				for (int i = 0; i < wall.sum; i++)
				{
					putimage(wall.wcoor[i].x, wall.wcoor[i].y, &wallimage);
				}
				MoveSnake();
				Sleep(500 - GetSpeed(snake.n));
				EatFood();
				CollisionDetection();
				if (againflag == 1)
				{
					break;
				}
			}
			if (againflag == 1)
			{
				break;
			}
			GetDirection();
		}

	}
	return 0;
}

