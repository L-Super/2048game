#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<conio.h>

#define GRID_W 100//格子宽度
#define MAX_SIZE 4//每行每列格子数量
#define INTERVAL 15//间距
#define WIN_SIZE MAX_SIZE*GRID_W+INTERVAL*(MAX_SIZE+1)//窗口宽度高度

enum Color//枚举格子颜色
{
	zero = RGB(205, 193, 180),//0的颜色
	twoTo1 = RGB(238, 228, 218),//2的颜色
	twoTo2 = RGB(237, 224, 200),//4的颜色
	twoTo3 = RGB(242, 177, 121),//8的颜色
	twoTo4 = RGB(245, 149, 99),//16的颜色
	twoTo5 = RGB(246, 124, 95),//32的颜色
	twoTo6 = RGB(246, 94, 59),//64的颜色
	twoTo7 = RGB(242, 177, 121),//128的颜色
	twoTo8 = RGB(237, 204, 97),//256的颜色
	twoTo9 = RGB(255, 0, 128),//512的颜色
	twoTo10 = RGB(145, 0, 72),//1024的颜色
	twoTo11 = RGB(242, 17, 158),//2048的颜色
	back = RGB(187, 173, 160),//背景颜色
};
Color arr[13] = { zero,twoTo1,twoTo2,twoTo3,twoTo4,twoTo5,twoTo6,twoTo7,twoTo8,twoTo9,twoTo10,twoTo11,back };

//定义数组，存储数据,全局变量自动初始化为0
int map[MAX_SIZE][MAX_SIZE];

//随机产生一个整数2或4，2概率比4大
int createNum()
{
	//随机数 rand() 加上头文件
	srand((unsigned)time(NULL)+clock());
	printf("%d",rand());
	if (rand() % 6 == 0)
		return 4;
	else
		return 2;
	//return 0;
}

//初始化数据
void gameInit()
{
	for(int i=0;i<2;/*i++*/)
	{
		int r = rand() % MAX_SIZE;
		int c = rand() % MAX_SIZE;
		if (map[r][c] == 0)
		{
			map[r][c] = createNum();
			i++;
		}
		
	}

}

//绘制界面
void gameDraw()
{
	//设置背景颜色
	setbkcolor(RGB(187,173,160));
	//清除绘图设备
	cleardevice();
	//绘制矩形
	/*
	rectangle(20,20,80,80);//空心矩形
	solidrectangle(120, 120, 180, 180);//实心矩形（可填充颜色)
	*/
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int k = 0; k < MAX_SIZE; k++)
		{
			//找到对应格子左上角坐标
			int x = k * GRID_W+(k+1)*INTERVAL;
			int y=i* GRID_W + (i + 1) * INTERVAL;
			//设置格子填充颜色
			//setfillcolor(RGB(205, 193, 180));
			int index = (int) log2((double)map[i][k]);
			COLORREF tcolor = arr[index];
			setfillcolor(tcolor);

			//绘制格子
			//solidrectangle(x, y, x + GRID_W, y + GRID_W);
			//圆角
			solidroundrect(x, y, x + GRID_W, y + GRID_W,10,10);
			if (map[i][k] != 0)
			{
				//数组数据绘制到窗口上
				/*
				注意：输出文字的时候，可能会有错误
					报错：error C2665 : "outtextxy" : 2个重载中没有一个可以转换所有参数类型
					解决方法：点击菜单栏->项目->属性->高级->字符集->改为多字节字符集即可
				*/
				//outtextxy(20, 20, _T("h"));
				//设置文字属性
				settextstyle(50, 0, "黑体");
				//设置文字背景透明
				setbkmode(TRANSPARENT);
				settextcolor(RGB(119, 110, 101));
			
				//int to char
				char str[10] = "";

				sprintf_s(str,"%d", map[i][k]);
				//求字符串的宽度高度
				int tw = textwidth(str);
				int th = textheight(str);
				int tx = (GRID_W - tw) / 2;
				int ty = (GRID_W - th) / 2;
			
				outtextxy(x+tx, y+ty, str);

			}
			printf("%d", map[i][k]);
		}
	}
}

//移动数组数据
void moveUP()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_SIZE; begin++)
		{
			
			if (map[begin][i] != 0)
				if (map[temp][i] == 0)
				{
					//(0,0)等于0,把（0，i)赋值过去
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					//(0,0)等于（0，i),相加
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
					//只移动一次
					temp++;
				}
				else
				{
					//（0，0）不等（0，i),上移(0,i)，并清零
					map[temp + 1][i] = map[begin][i];
					if (temp + 1 != begin)
					{
						map[begin][i] = 0;
					}

					temp++;
				}

		}
	}
}
void moveDown()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		int temp = 3;
		for (int begin = 0; begin < MAX_SIZE-1; begin++)
		{

			if (map[begin][i] != 0)
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
					temp--;
				}
				else
				{
					map[temp - 1][i] = map[begin][i];
					if (temp - 1 != begin)
					{
						map[begin][i] = 0;
					}
					temp--;
				}

		}
	}
}
void moveRight()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		int temp = 3;
		for (int begin = 0; begin < MAX_SIZE - 1; begin++)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
					temp--;
				}
				else
				{
					map[i][temp - 1] = map[i][begin];
					if (temp - 1 != begin)
						map[i][begin] = 0;
					temp--;
				}
			}
		}
	}
}
void moveLeft()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_SIZE; begin++)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
					temp++;
				}
				else
				{
					map[i][temp + 1] = map[i][begin];
					if (temp + 1 != begin)
						map[i][begin] = 0;
					temp++;
				}
			}
		}
	}

}
//按键处理
void keyDeal()
{
	//获取键盘按键
	char key = _getch();
	switch (key)
	{
	case 'w':
	case 'W':
	case 72:
		moveUP();
		break;
	case 's':
	case 'S':
	case 80:
		moveDown();
		break;
	case 'a':
	case 'A':
	case 75:
		moveLeft();
		break;
	case 'd':
	case 'D':
	case 77:
		moveRight();
		break;

	default:
		break;
	}
}


int main()
{
	//create windows
	initgraph(WIN_SIZE,WIN_SIZE,SHOWCONSOLE);
	
	
	/*while (1)
	{
		printf("%d", createNum());
		Sleep(200);
	}
		*/
	//createNum();
	
	while (1)
	{
		gameInit();
		gameDraw();
		keyDeal();
	}
	//system("pause");
	closegraph();//close
	return 0;
}