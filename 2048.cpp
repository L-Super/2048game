#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<conio.h>

#define GRID_W 100//���ӿ��
#define MAX_SIZE 4//ÿ��ÿ�и�������
#define INTERVAL 15//���
#define WIN_SIZE MAX_SIZE*GRID_W+INTERVAL*(MAX_SIZE+1)//���ڿ�ȸ߶�

enum Color//ö�ٸ�����ɫ
{
	zero = RGB(205, 193, 180),//0����ɫ
	twoTo1 = RGB(238, 228, 218),//2����ɫ
	twoTo2 = RGB(237, 224, 200),//4����ɫ
	twoTo3 = RGB(242, 177, 121),//8����ɫ
	twoTo4 = RGB(245, 149, 99),//16����ɫ
	twoTo5 = RGB(246, 124, 95),//32����ɫ
	twoTo6 = RGB(246, 94, 59),//64����ɫ
	twoTo7 = RGB(242, 177, 121),//128����ɫ
	twoTo8 = RGB(237, 204, 97),//256����ɫ
	twoTo9 = RGB(255, 0, 128),//512����ɫ
	twoTo10 = RGB(145, 0, 72),//1024����ɫ
	twoTo11 = RGB(242, 17, 158),//2048����ɫ
	back = RGB(187, 173, 160),//������ɫ
};
Color arr[13] = { zero,twoTo1,twoTo2,twoTo3,twoTo4,twoTo5,twoTo6,twoTo7,twoTo8,twoTo9,twoTo10,twoTo11,back };

//�������飬�洢����,ȫ�ֱ����Զ���ʼ��Ϊ0
int map[MAX_SIZE][MAX_SIZE];

//�������һ������2��4��2���ʱ�4��
int createNum()
{
	//����� rand() ����ͷ�ļ�
	srand((unsigned)time(NULL)+clock());
	printf("%d",rand());
	if (rand() % 6 == 0)
		return 4;
	else
		return 2;
	//return 0;
}

//��ʼ������
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

//���ƽ���
void gameDraw()
{
	//���ñ�����ɫ
	setbkcolor(RGB(187,173,160));
	//�����ͼ�豸
	cleardevice();
	//���ƾ���
	/*
	rectangle(20,20,80,80);//���ľ���
	solidrectangle(120, 120, 180, 180);//ʵ�ľ��Σ��������ɫ)
	*/
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int k = 0; k < MAX_SIZE; k++)
		{
			//�ҵ���Ӧ�������Ͻ�����
			int x = k * GRID_W+(k+1)*INTERVAL;
			int y=i* GRID_W + (i + 1) * INTERVAL;
			//���ø��������ɫ
			//setfillcolor(RGB(205, 193, 180));
			int index = (int) log2((double)map[i][k]);
			COLORREF tcolor = arr[index];
			setfillcolor(tcolor);

			//���Ƹ���
			//solidrectangle(x, y, x + GRID_W, y + GRID_W);
			//Բ��
			solidroundrect(x, y, x + GRID_W, y + GRID_W,10,10);
			if (map[i][k] != 0)
			{
				//�������ݻ��Ƶ�������
				/*
				ע�⣺������ֵ�ʱ�򣬿��ܻ��д���
					����error C2665 : "outtextxy" : 2��������û��һ������ת�����в�������
					�������������˵���->��Ŀ->����->�߼�->�ַ���->��Ϊ���ֽ��ַ�������
				*/
				//outtextxy(20, 20, _T("h"));
				//������������
				settextstyle(50, 0, "����");
				//�������ֱ���͸��
				setbkmode(TRANSPARENT);
				settextcolor(RGB(119, 110, 101));
			
				//int to char
				char str[10] = "";

				sprintf_s(str,"%d", map[i][k]);
				//���ַ����Ŀ�ȸ߶�
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

//�ƶ���������
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
					//(0,0)����0,�ѣ�0��i)��ֵ��ȥ
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					//(0,0)���ڣ�0��i),���
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
					//ֻ�ƶ�һ��
					temp++;
				}
				else
				{
					//��0��0�����ȣ�0��i),����(0,i)��������
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
//��������
void keyDeal()
{
	//��ȡ���̰���
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