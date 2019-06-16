// snake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
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
	snake.scoor[0].x = 320;
	snake.scoor[0].y = 240;
	snake.n = 2;
	snake.direction = goright;
	food.flag = 0;
}
void ProduceFood()
{
	srand(unsigned(time(0)));
	food.fcoor.x = (rand() % 31 + 1) * 20;
	food.fcoor.y = (rand() % 23 + 1) * 20;
	food.flag = 1;
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
int main()
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
				Sleep(400);
				ProduceFood();
			}
			cleardevice();
			putimage(food.fcoor.x, food.fcoor.y, &foodimage);
			MoveSnake();
			Sleep(400);
			EatFood();
		}
		GetDirection();
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
