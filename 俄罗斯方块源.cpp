#include<iostream>
#include<string>
#include<windows.h>
#include<easyx.h>
#include<cstdlib>
#include<ctime>
#include <conio.h>
#include<random>
#define pxsize 10

int stop1 = 0;
int isrotate = 0;
int vx = 0;
int vy = 0;
int begin_x = 50;
int begin_y = 130;
int blocks[7][4] = { 
	{3,5,4,7},
	{1,3,5,7},
	{2,3,4,5},
	{2,3,5,7},
	{3,5,7,6},
	{2,4,5,7},
	{3,5,4,6} };
int haveground = 0;
class point {
public:
	int x, y; // �� ��
};
struct bkcolor{
	int r1, g1, b1; // �߿���ɫ
	int r2, g2, b2; // �����ɫ
};
//class nowblock {
//public:
//	int x, y;   // ��������
//	int block;  // ��������
//	point smblock[4]; // �������
//	// 1~7 1 �ڿ��� 2 ���� 3 ������ 4 7���� 5��7 6 Z���� 8 ��Z
//	// 1 �ڿ��� 3 5 4 7
//	// 2 ���� 1 3 5 7
//	// 3 ������ 2 3 4 5
//	// 4 7���� 2 3 5 7
//	// 5 ��7 3 5 7 6
//	// 6 Z���� 2 4 5 7
//	// 7 ��Z 3 5 4 6
//	int toward; // ���� 0 1
//};
class block {
public:
	block() {
		// ʹ�õ�ǰʱ����Ϊ���������
			// ����һ�����������
		std::random_device rd;
		std::mt19937 gen(rd());

		// ����һ�����ȷֲ�����Χ��0��6֮��
		std::uniform_int_distribution<> dis(0, 6);
		typ = dis(gen);
		// ���ɷ�Χ�� 1 �� 7 ֮��������
		for (int i = 0; i < 4; i++) {
			smblock[i].x = blocks[typ][i] % 2 + 5;
			smblock[i].y = blocks[typ][i] / 2;
		}
	}
public:
	int typ;
	point smblock[4];
	static bkcolor img[7];
};
block btemp;
bkcolor block::img[7] = { 
{239, 125, 200, 253, 208, 222},
{100, 100, 208, 135, 206, 235},
{0, 128, 0, 0, 255, 0},
{139, 69, 19, 210, 105, 30},
{139, 69, 19, 210, 105, 30},
{255, 215, 0, 255, 255, 0},
{255, 215, 0, 255, 255, 0} };
class GameMessage {
public:
	int score;
	int speed;
	int next;
};
// ��������  ������ \(^v^)/
void drawnext(block next); // ����һ��
void showwelcome(); // ��ʾ��ӭ����
void solvekeymsg(block* now, block next);
bool isgameover(); // �ж���Ϸ�Ƿ����
int mousemsg(); // �����Ϣ
bool isinarea(int mx, int my, int x1, int y1, int x2, int y2);	// �ж�����Ƿ���������
void to_select(); // ѡ��
void gameplay(); // ��Ϸ����
void gamesetting(); // ��Ϸ����
void gamehelp(); // ��Ϸ����
void gameexit(); // �˳���Ϸ
void keymsg(block *now); // ������Ϣ
void drop(block* nblock); // ����
void rotate(block* nblock); // ��ת
// ������
void drawblock(block nblock);
// �Ʒ�
int overmousemsg();
void score();
void drawgameframe(block next);// ����Ϸ���
ExMessage msg = { 0 };
ExMessage msgkey = { 0 };
int main()
{
	// ����һ�����������
	std::random_device rd;
	std::mt19937 gen(rd());

	// ����һ�����ȷֲ�����Χ��1��100֮��
	std::uniform_int_distribution<> dis(1, 100);
	while (1) {
		to_select();
	}
	return 0;
}
void showwelcome()
{
	int x = 0, y = 0;
	x = getwidth();
	y = getheight();
	settextcolor(RGB(231, 113, 215));//����������ɫΪ�����ÿ��ķۺ�ɫ
	settextstyle(50, 0, _T("����"));//���������СΪ50������Ϊ����
	int centerX = (x - textwidth(_T("�� ӭ �� �� �� �� ˹ �� �� �� (-��-) /"))) / 2;
	outtextxy(centerX, 70, _T("�� ӭ �� �� �� �� ˹ �� �� �� (-��-��/"));//�������
	// �� �� �� ʵ�� ���� ʵ��
	setlinestyle(PS_SOLID, 8);//�����������Ϊʵ��
	setlinecolor(RGB(253, 208, 222));//����������ɫΪ�ۺ�ɫ ���Ǻ�ǳ
	line(6, 10, 1195, 10);
	line(6, 645, 1195, 645);
	line(6, 10, 6, 645);
	line(1195, 10, 1195, 645);
	setlinestyle(PS_DASH, 5);//�����������Ϊ����
	setlinecolor(RGB(71, 166, 74));//����������ɫΪ��ɫ
	line(14, 18, 1187, 18);	
	line(14, 637, 1187, 637);
	line(14, 18, 14, 637);
	line(1187, 18, 1187, 637);
	setlinestyle(PS_SOLID, 8);//�����������Ϊʵ��
	setlinecolor(RGB(253, 208, 222));//����������ɫΪ�ۺ�ɫ ���Ǻ�ǳ
	line(22, 26, 1179, 22);
	line(22, 629, 1179, 629);
	line(22, 26, 22, 629);
	line(1179, 26, 1179, 629);
	// ��һ�¶���˹���� ����״
	// �ڿ��� ��� ����Ҫ�ۺ�ɫ��
	setlinecolor(RGB(239, 125, 200));//���ñ߿���ɫΪ�ۺ�ɫ
	setlinestyle(PS_SOLID ,3);//����������ϸΪ5
	setfillcolor(RGB(253, 208, 222));//���������ɫΪ�ۺ�ɫ
	fillrectangle(120, 240, 160, 280);
	fillrectangle(80, 200, 120, 240);
	fillrectangle(120, 200, 160, 240);
	fillrectangle(160, 200, 200, 240);
	// ���� ���ҵȲ����� ��ɫ�� ����������ɡ���������
	setlinecolor(RGB(100, 100, 208));//���ñ߿���ɫΪ��ɫ
	setlinestyle(PS_SOLID, 3);//����������ϸΪ3
	setfillcolor(RGB(135, 206, 235));//���������ɫΪ����ɫ
	fillrectangle(160, 500, 200, 540);
	fillrectangle(200, 500, 240, 540);
	fillrectangle(240, 500, 280, 540);
	fillrectangle(280, 500, 320, 540);
	// ������  ��ɫ��
	setlinecolor(RGB(0, 128, 0));//���ñ߿���ɫΪ����ɫ
	setlinestyle(PS_SOLID, 3);//����������ϸΪ3
	setfillcolor(RGB(0, 255, 0));//���������ɫΪǳ��ɫ
	fillrectangle(100, 360, 140, 400);
	fillrectangle(140, 360, 180, 400);
	fillrectangle(100, 400, 140, 440);
	fillrectangle(140, 400, 180, 440);
	// 7���� ������ ��ɫ��
	setlinecolor(RGB(139, 69, 19));//���ñ߿���ɫΪ��ɫ
	setlinestyle(PS_SOLID, 3);//����������ϸΪ3
	setfillcolor(RGB(210, 105, 30));//���������ɫΪ�ɿ���ɫ
	fillrectangle(280, 240, 320, 280);
	fillrectangle(320, 240, 360, 280);
	fillrectangle(360, 240, 400, 280);
	fillrectangle(360, 200, 400, 240);
	
	//  Z ���� �����ᣡ�� ��ɫ��
	setlinecolor(RGB(255, 215, 0));//���ñ߿���ɫΪ���ɫ
	setlinestyle(PS_SOLID, 3);//����������ϸΪ3
	setfillcolor(RGB(255, 255, 0));//���������ɫΪ��ɫ
	fillrectangle(360, 400, 400, 440);
	fillrectangle(280, 360, 320, 400);
	fillrectangle(320, 360, 360, 400);
	fillrectangle(320, 400, 360, 440);
	// �ָ���  �ұ�����˵�
	setlinecolor(RGB(201, 151, 242));//����������ɫΪ��ɫ
	setlinestyle(PS_SOLID, 8);//�����������Ϊʵ��
	line(500, 170, 500, 620);
	// ����˵�
	settextcolor(RGB(210, 105, 30));//����������ɫΪ�ɿ���ɫ
	settextstyle(50, 0, _T("�ֺ���"));//���������СΪ50������Ϊ����
	int centermX1 = (1200 - 500 - textwidth(_T("�� Ϸ �� ��"))) / 2;
	outtextxy(500 + centermX1, 200, _T("�� Ϸ �� ��"));//�������


	//1.��ʼ�� ���ƻ�ɫ�߿�
	setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
	setlinestyle(PS_SOLID, 5);//����������ϸΪ5
	setfillcolor(WHITE);//���������ɫΪ��ɫ
	fillrectangle(600, 300, 800, 350);
	settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
	settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
	int centerX1 = (200 - textwidth(_T("��ʼ��Ϸ"))) / 2;
	int centerY1 = (50 - textheight(_T("��ʼ��Ϸ"))) / 2;
	outtextxy(600 + centerX1, 300 + centerY1, _T("��ʼ��Ϸ"));//�������
	//2.��Ϸ����
	setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
	setlinestyle(PS_SOLID, 5);//����������ϸΪ5
	setfillcolor(WHITE);//���������ɫΪ��ɫ
	fillrectangle(600, 450, 800, 500);
	settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
	settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
	int centerX2 = (200 - textwidth(_T("��Ϸ����"))) / 2;
	int centerY2 = (50 - textheight(_T("��Ϸ����"))) / 2;
	outtextxy(600 + centerX2, 450 + centerY2, _T("��Ϸ����"));//�������
	//3.��Ϸ����
	setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
	setlinestyle(PS_SOLID, 5);//����������ϸΪ5
	setfillcolor(WHITE);//���������ɫΪ��ɫ
	fillrectangle(890, 300, 1090, 350);
	settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
	settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
	int centerX3 = (200 - textwidth(_T("��Ϸ����"))) / 2;
	int centerY3 = (50 - textheight(_T("��Ϸ����"))) / 2;
	outtextxy(890 + centerX3, 300 + centerY3, _T("��Ϸ����"));//�������
	
	//4.�˳���Ϸ
	setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
	setlinestyle(PS_SOLID, 5);//����������ϸΪ5
	setfillcolor(WHITE);//���������ɫΪ��ɫ
	fillrectangle(890, 450, 1090, 500);
	settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
	settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
	int centerX4 = (200 - textwidth(_T("�˳���Ϸ"))) / 2;
	int centerY4 = (50 - textheight(_T("�˳���Ϸ"))) / 2;
	outtextxy(890 + centerX4, 450 + centerY4, _T("�˳���Ϸ"));//�������

}
void clearFullLines();
void drawline(); 
const int GAME_WIDTH = 12;
const int GAME_HEIGHT = 19;
bool gameMap[GAME_HEIGHT + 1][GAME_WIDTH + 1] = { false };
GameMessage game;
bool iscrash(block now)
{
	for (int i = 0; i < 4; i++) {
		int blockX = now.smblock[i].x;
		int blockY = now.smblock[i].y;
		if (blockY >= GAME_HEIGHT || blockX < 0 || blockX >= GAME_WIDTH) {
			return true;
		}
		if (gameMap[blockY][blockX]) {
			return true;
		}
	}
	return false;
}

void landBlock(block now) {
	for (int i = 0; i < 4; i++) {
		int blockX = now.smblock[i].x;
		int blockY = now.smblock[i].y;
		gameMap[blockY - 1][blockX] = true;
	}
	clearFullLines();
}
void to_select()
{

	initgraph(1200, 650, EX_NOCLOSE | EX_SHOWCONSOLE | EX_NOMINIMIZE | EX_DBLCLKS);//��ʼ������
	//setbkcolor(RGB(231, 113, 215));//���ñ�����ɫΪ�ۺ�ɫ ���� ���� �ۺ�ɫ�����ҿ�Ϲ��
	setbkcolor(WHITE);//���ñ�����ɫΪ��ɫ �Ƚϲ�Ϲ��
	cleardevice(); // ����
	showwelcome();
	peekmessage(&msg, EX_MOUSE);// ��ȡ�����Ϣ
	int mode = -1;
	peekmessage(&msg, EX_MOUSE);// ��ȡ�����Ϣ
	peekmessage(&msg, EX_MOUSE);// ��ȡ�����Ϣ
	mode = mousemsg();
	switch (mode)
		{
		case 1:
		{
			// ��ʼ��Ϸ
			{
				std::cout << "ѡ��ģʽ����ʼ��Ϸ �������Դ�����" << std::endl;
				closegraph();
				gameplay();
			}
			break;
		}
		case 2:
		{
			// ��Ϸ����
			{
				int mode = -1;
				cleardevice();
				gamesetting();
			}
			break;
		}
		case 3:
		{
			// ��Ϸ����
			{
				int mode = -1;
				std::cout << "�û�ѡ����Ϸ����" << std::endl;
				closegraph();
				gamehelp();
			}
			break;
		}
		case 4:
		{
			{
				int mode = -1;
				// �˳���Ϸ
				gameexit();
				break;
			}
		}
	}
}
int mousemsg()
{
	int yes = 0;
	while (1) {
		
		peekmessage(&msg, EX_MOUSE);// ��ȡ�����Ϣ
		if (isinarea(msg.x, msg.y, 600, 300, 800, 350) && yes == 0) {
			setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
			setlinestyle(PS_SOLID, 5);//����������ϸΪ5
			setfillcolor(RGB(231, 113, 215));//���������ɫΪ��ɫ
			fillrectangle(600, 300, 800, 350);
			//settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
			//settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
			//int centerX1 = (200 - textwidth(_T("��ʼ��Ϸ"))) / 2;
			//int centerY1 = (50 - textheight(_T("��ʼ��Ϸ"))) / 2;
			//outtextxy(600 + centerX1, 300 + centerY1, _T("��ʼ��Ϸ"));//�������
			yes = 1;	
		}
		else if (isinarea(msg.x, msg.y, 600, 450, 800, 500) && yes == 0) {
			setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
			setlinestyle(PS_SOLID, 5);//����������ϸΪ5
			setfillcolor(RGB(231, 113, 215));//���������ɫΪ��ɫ
			fillrectangle(600, 450, 800, 500);
			//settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
			//settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
			//int centerX1 = (200 - textwidth(_T("��Ϸ����"))) / 2;
			//int centerY1 = (50 - textheight(_T("��Ϸ����"))) / 2;
			//outtextxy(600 + centerX1, 450 + centerY1, _T("��Ϸ����"));//�������
			yes = 1;	
		}
		else if (isinarea(msg.x, msg.y, 890, 300, 1090, 350) && yes == 0) {
			setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
			setlinestyle(PS_SOLID, 5);//����������ϸΪ5
			setfillcolor(RGB(231, 113, 215));//���������ɫΪ��ɫ
			fillrectangle(890, 300, 1090, 350);
			//settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
			//settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
			//int centerX1 = (200 - textwidth(_T("��Ϸ����"))) / 2;
			//int centerY1 = (50 - textheight(_T("��Ϸ����"))) / 2;
			//outtextxy(890 + centerX1, 300 + centerY1, _T("��Ϸ����"));//�������
			yes = 1;
		}
		else if (isinarea(msg.x, msg.y, 890, 450, 1090, 500) && yes == 0) {
			setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
			setlinestyle(PS_SOLID, 5);//����������ϸΪ5
			setfillcolor(RGB(231, 113, 215));//���������ɫΪ��ɫ
			fillrectangle(890, 450, 1090, 500);
			//settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
			//settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
			//int centerX1 = (200 - textwidth(_T("�˳���Ϸ"))) / 2;
			//int centerY1 = (50 - textheight(_T("�˳���Ϸ"))) / 2;
			//outtextxy(890 + centerX1, 450 + centerY1, _T("�˳���Ϸ"));//�������
			yes = 1;
		}
		else if (!isinarea(msg.x, msg.y, 600, 300, 800, 350) && !isinarea(msg.x, msg.y, 600, 450, 800, 500) && !isinarea(msg.x, msg.y, 890, 300, 1090, 350) && !isinarea(msg.x, msg.y, 890, 450, 1090, 500))
		{
			if (yes == 1) {
				//1.��ʼ�� ���ƻ�ɫ�߿�
				setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
				setlinestyle(PS_SOLID, 5);//����������ϸΪ5
				setfillcolor(WHITE);//���������ɫΪ��ɫ
				fillrectangle(600, 300, 800, 350);
				settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
				settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
				int centerX1 = (200 - textwidth(_T("��ʼ��Ϸ"))) / 2;
				int centerY1 = (50 - textheight(_T("��ʼ��Ϸ"))) / 2;
				outtextxy(600 + centerX1, 300 + centerY1, _T("��ʼ��Ϸ"));//�������
				//2.��Ϸ����
				setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
				setlinestyle(PS_SOLID, 5);//����������ϸΪ5
				setfillcolor(WHITE);//���������ɫΪ��ɫ
				fillrectangle(600, 450, 800, 500);
				settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
				settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
				int centerX2 = (200 - textwidth(_T("��Ϸ����"))) / 2;
				int centerY2 = (50 - textheight(_T("��Ϸ����"))) / 2;
				outtextxy(600 + centerX2, 450 + centerY2, _T("��Ϸ����"));//�������
				//3.��Ϸ����
				setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
				setlinestyle(PS_SOLID, 5);//����������ϸΪ5
				setfillcolor(WHITE);//���������ɫΪ��ɫ
				fillrectangle(890, 300, 1090, 350);
				settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
				settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
				int centerX3 = (200 - textwidth(_T("��Ϸ����"))) / 2;
				int centerY3 = (50 - textheight(_T("��Ϸ����"))) / 2;
				outtextxy(890 + centerX3, 300 + centerY3, _T("��Ϸ����"));//�������

				//4.�˳���Ϸ
				setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
				setlinestyle(PS_SOLID, 5);//����������ϸΪ5
				setfillcolor(WHITE);//���������ɫΪ��ɫ
				fillrectangle(890, 450, 1090, 500);
				settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
				settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
				int centerX4 = (200 - textwidth(_T("�˳���Ϸ"))) / 2;
				int centerY4 = (50 - textheight(_T("�˳���Ϸ"))) / 2;
				outtextxy(890 + centerX4, 450 + centerY4, _T("�˳���Ϸ"));//�������
				yes = 0;
			}
		}
		if (msg.message == WM_LBUTTONDBLCLK && isinarea(msg.x, msg.y, 600, 300, 800, 350)) {
			return 1;
		}
		else if (msg.message == WM_LBUTTONDBLCLK && isinarea(msg.x, msg.y, 600, 450, 800, 500)) {
			return 2;
		}
		else if (msg.message == WM_LBUTTONDBLCLK && isinarea(msg.x, msg.y, 890, 300, 1090, 350)) {
			return 3;
		}
		else if (msg.message == WM_LBUTTONDBLCLK	 && isinarea(msg.x, msg.y, 890, 450, 1090, 500)) {
			return 4;
		}
	}
}
void overselect();
void cleanblock(block now);// ��������
bool isinarea(int mx, int my, int x1, int y1, int x2, int y2)
{
	if (mx > x1 && mx < x2 && my > y1 && my < y2) {
		return true;
	}
	else {
		return false;
	}
}
void gameplay()
{
	initgraph(600, 800, EX_NOCLOSE | EX_SHOWCONSOLE | EX_NOMINIMIZE | EX_DBLCLKS);//��ʼ����Ϸ����
	setbkcolor(WHITE);//���ñ�����ɫΪ��ɫ
	GameMessage game;
	game.score = 0;
	game.speed = 1;
	game.next = 0;
	block now;

	Sleep(1000);
	while (1) { // ��Ϸѭ��
		haveground = 0;
		block next;
		drawgameframe(next); // ����Ϸ���
		while (1) // �������� ѭ��
		{
			setlinecolor(RED);//����������ɫΪ��ɫ
			setlinestyle(PS_DOT, 5);//�����������Ϊ����
			line(52, 150, 300, 150);
			drawblock(now); // ������
			// �ж��Ƿ񵽵�
			if (iscrash(now)) {
				landBlock(now);
				std::cout << "�������" << std::endl;
				if (isgameover()) {
					std::cout << "��Ϸ����" << std::endl;
						for (int k = 0; k < 19; k++) {
							for (int j = 0; j < 12; j++) {
								gameMap[k][j] = false;
							}
						}
						drawblock(now);
					overselect();

				}
				for (int i = 0; i < 4; i++) {
				std::cout << "���鵽����" << "X:" << now.smblock[i].x << "Y:" << now.smblock[i].y << std::endl;
			}
				break;
			}
			keymsg(&now); // ���̲���
			Sleep(100);
			solvekeymsg(&now, next);
			keymsg(&now);
			Sleep(100);
			solvekeymsg(&now,next);
			keymsg(&now);
			Sleep(100);
			solvekeymsg(&now, next);
			cleanblock(now);
			drop(&now); // ����
			haveground = 0;
			//drawgameframe(game, next); // ����Ϸ���
			std::cout << "��������" << std::endl;
			// ������

		}
		now = next;
	}
}
void gamesetting()
{
	initgraph(800, 600, EX_NOCLOSE | EX_SHOWCONSOLE | EX_NOMINIMIZE | EX_DBLCLKS);
	setbkcolor(WHITE);//���ñ�����ɫΪ��ɫ �Ƚϲ�Ϲ��
	cleardevice(); // ����
	settextcolor(RGB(0, 0, 255));//����������ɫΪ�ۺ�ɫ
	settextstyle(80, 0, _T("����"));//���������СΪ30������Ϊ����
	outtextxy(20, 20, _T("����˹����"));
	outtextxy(20, 120, _T("�㻹������ʲô������"));
	outtextxy(20, 220, _T("���������"));
	outtextxy(20, 320, _T("����󷵻����˵�"));
	Sleep(5000);
	to_select();
}
void gamehelp()
{
	initgraph(800, 600, EX_NOCLOSE | EX_SHOWCONSOLE | EX_NOMINIMIZE | EX_DBLCLKS);
	setbkcolor(WHITE);//���ñ�����ɫΪ��ɫ �Ƚϲ�Ϲ��
	cleardevice(); // ����
	settextcolor(RGB(0, 0, 255));//����������ɫΪ�ۺ�ɫ
	settextstyle(80, 0, _T("����"));//���������СΪ30������Ϊ����
	outtextxy(20, 20, _T("��---��ת"));
	outtextxy(400, 20, _T("��---����"));
	outtextxy(20, 400, _T("��---����"));
	outtextxy(400, 400, _T("��---����"));
	setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
	setlinestyle(PS_SOLID, 5);//����������ϸΪ5
	setfillcolor(WHITE);//���������ɫΪ��ɫ
	fillrectangle(400, 300, 600, 350);
	settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
	settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
	int centerX1 = (200 - textwidth(_T("���˵�"))) / 2;
	int centerY1 = (50 - textheight(_T("���˵�"))) / 2;
	outtextxy(400 + centerX1, 300 + centerY1, _T("���˵�"));//�������
	int yes2 = 0;
	peekmessage(&msg, EX_MOUSE);// ��ȡ�����Ϣ
	while (1) {
		peekmessage(&msg, EX_MOUSE);// ��ȡ�����Ϣ
		if (yes2 == 1 && isinarea(msg.x, msg.y, 400, 300, 600, 350))
		{
			setfillcolor(RGB(128,128,128));//���������ɫΪ��ɫ
			fillrectangle(400, 300, 600, 350);
			yes2 = 0;
		}
		if (yes2 == 0 && !isinarea(msg.x, msg.y, 400, 300, 600, 350))
		{
			setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
			setlinestyle(PS_SOLID, 5);//����������ϸΪ5
			setfillcolor(WHITE);//���������ɫΪ��ɫ
			fillrectangle(400, 300, 600, 350);
			settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
			settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
			int centerX1 = (200 - textwidth(_T("���˵�"))) / 2;
			int centerY1 = (50 - textheight(_T("���˵�"))) / 2;
			outtextxy(400 + centerX1, 300 + centerY1, _T("���˵�"));//�������
			yes2 = 1;
		}
		if (msg.message == WM_LBUTTONDBLCLK && isinarea(msg.x, msg.y, 400, 300, 600, 350)) {
			to_select();
		}
	}
}
void gameexit()
{
	closegraph();
	exit(0);
}
void drawblock(block nblock)
{
	if (iscrash(nblock))return;
	int r1 = nblock.img[nblock.typ].r1;
	int g1 = nblock.img[nblock.typ].g1;
	int b1 = nblock.img[nblock.typ].b1;
	int r2 = nblock.img[nblock.typ].r2;
	int g2 = nblock.img[nblock.typ].g2;
	int b2 = nblock.img[nblock.typ].b2;
	int x[4], y[4];
	for (int i = 0; i < 4; i++) {
		x[i] = nblock.smblock[i].x * 20 + begin_x;
		y[i] = nblock.smblock[i].y * 20 + begin_y;
	}
	setlinecolor(RGB(r1, g1, b1));//���ñ߿���ɫ
	setfillcolor(RGB(r2, g2, b2));//���������ɫ
	setlinestyle(PS_SOLID, 1);//�����������Ϊʵ��
	for (int i = 0; i < 4; i++) {
		fillrectangle(x[i], y[i], x[i] + 20, y[i] + 20);
	}
}
void drawgameframe(block next)
{
	// ����Ϸ���

	if (!haveground) {
		setbkcolor(WHITE);
		cleardevice();//����
		setlinecolor(RGB(253, 208, 222));//����������ɫΪ�ۺ�ɫ
		setlinestyle(PS_SOLID, 5);//�����������Ϊʵ��
		line(6, 10, 595, 10);
		line(6, 795, 595, 795);
		line(6, 10, 6, 795);
		line(595, 10, 595, 795);
		setlinestyle(PS_DASH, 5);//�����������Ϊ����
		setlinecolor(RGB(71, 166, 74));//����������ɫΪ��ɫ
		line(14, 18, 585, 18);
		line(14, 787, 585, 787);
		line(14, 18, 14, 787);
		line(585, 18, 585, 787);
		setlinecolor(RGB(253, 208, 222));//����������ɫΪ�ۺ�ɫ
		setlinestyle(PS_SOLID, 5);//�����������Ϊʵ��
		line(22, 26, 575, 26);
		line(22, 779, 575, 779);
		line(575, 26, 575, 779);
		line(22, 26, 22, 779);
		// ������������� ��ɫʵ��
		setlinecolor(BLACK);//����������ɫΪ��ɫ
		setlinestyle(PS_SOLID, 5);//�����������Ϊʵ��
		line(47, 130, 47, 513);
		line(47, 513, 293, 513);
		line(293, 513, 293, 130);
		setlinecolor(RED);//����������ɫΪ��ɫ
		setlinestyle(PS_DOT, 5);//�����������Ϊ����
		line(52, 150, 300, 150);

		// ������
		settextcolor(RGB(231, 113, 215));//����������ɫΪ�ۺ�ɫ
		settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
		outtextxy(80, 60, _T("������"));
		std::string temps = std::to_string(game.score);
		std::wstring wideStr = std::wstring(temps.begin(), temps.end());
		outtextxy(160, 62, wideStr.c_str());
		// ����һ��
		settextcolor(RGB(0, 0, 255));//����������ɫΪ�ۺ�ɫ
		settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
		outtextxy(370, 160, _T("�� һ ��"));
		setlinecolor(BLACK); //����������ɫΪ��ɫ
		setlinestyle(PS_DASH, 5);//�����������Ϊ����
		rectangle(350, 150, 550, 300);
		line(350, 200, 550, 200);
		drawnext(next);
		drawline();
		settextcolor(RGB(231, 113, 215));//����������ɫΪ�ۺ�ɫ
		settextstyle(24, 0, _T("����"));//���������СΪ30������Ϊ����
		outtextxy(60, 600, _T("ESC + SPACE --- ��ͣ"));
		haveground = 1;	// ������
	}
}
//point whatblock()
//{
//// 1~7 1 �ڿ��� 2 ���� 3 ������ 4 7���� 5��7 6 Z���� 8 ��Z
//// 1 �ڿ��� 3 5 4 7
//// 2 ���� 1 3 5 7
//// 3 ������ 2 3 4 5
//// 4 7���� 2 3 5 7
//// 5 ��7 3 5 7 6
//// 6 Z���� 2 4 5 7
//// 7 ��Z 3 5 4 6
//	// ʹ�õ�ǰʱ����Ϊ���������
//	std::srand(static_cast<unsigned int>(std::time(nullptr)));
//
//	// ���ɷ�Χ�� 1 �� 70 ֮��������
//		int Num = std::rand() % 70 + 1;
//		point p[4];
//		if (Num >= 1 && Num <= 10) {
//			p[0].x = 2;
//			p[0].y = 2;
//		}
//
//}
void rotate(block* nblock) // ��ת
{
	btemp = *nblock;
	// ����ԭʼ״̬
	point original[4];
	for (int i = 0; i < 4; i++) {
		original[i] = nblock->smblock[i];
	}

	// ѡȡ���ĵ㣨����ѡ��ڶ���������Ϊ���ĵ㣩
	point center = nblock->smblock[1];

	// ʹ����ת���������ת
	for (int i = 0; i < 4; i++) {
		int dx = nblock->smblock[i].x - center.x;
		int dy = nblock->smblock[i].y - center.y;
		nblock->smblock[i].x = center.x - dy;
		nblock->smblock[i].y = center.y + dx;
	}

	// �����ת���Ƿ���ײ��Խ��
	if (iscrash(*nblock)) {
		// �ָ���ԭʼ״̬
		for (int i = 0; i < 4; i++) {
			nblock->smblock[i] = original[i];
		}
	}
}
void drop(block* nblock) // ����
{
	for (int i = 0; i < 4; i++) {
		nblock->smblock[i].y++;
	}
}
void cleanblock(block now) {
	int x[4], y[4];
	for (int i = 0; i < 4; i++) {
		x[i] = now.smblock[i].x * 20 + begin_x;
		y[i] = now.smblock[i].y * 20 + begin_y;
	}
	setlinecolor(WHITE);//���ñ߿���ɫ
	setfillcolor(WHITE);//���������ɫ
	setlinestyle(PS_SOLID, 1);//�����������Ϊʵ��
	for (int i = 0; i < 4; i++) {
		fillrectangle(x[i], y[i], x[i] + 20, y[i] + 20);
	}	

}
void drawline() {
	for (int i = 0; i < 19; i++) {
		for (int j = 0;j < 12; j++) {
			if (gameMap[i][j] == true) { //��ɫ����
				setlinecolor(BLACK);//����������ɫΪ��ɫ
				setfillcolor(RGB(128, 128, 128));//���������ɫΪ��ɫ
				fillrectangle(j * 20 + begin_x, i * 20 + begin_y,
					j * 20 + begin_x + 20, i * 20 + begin_y + 20);
			}
		}
	}

}
//bool iscrash(block now) {
//	for (int i = 0; i < 4; i++) {
//		if (now.smblock[i].y >= 20 || now.smblock[i].x < 0 || now.smblock[i].x <= 20) {
//			return true;
//		}
//	}
//	return false;
//}
bool isgameover() {
	for (int i = 0; i < 10; i++) {
		if (gameMap[0][i] == true) {
			return true;
		}
	}
	return false;
}
int overmousemsg() {
	int yes = 1;
	setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
	setlinestyle(PS_SOLID, 3);//����������ϸΪ5
	setfillcolor(WHITE);//���������ɫΪ��ɫ
	fillrectangle(0, 0, 145, 70);
	settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
	settextstyle(20, 0, _T("����"));//���������СΪ30������Ϊ����
	int centerX3 = (145 - textwidth(_T("����һ��"))) / 2;
	int centerY3 = (70 - textheight(_T("����һ��"))) / 2;
	outtextxy(0 + centerX3, 0 + centerY3, _T("����һ��"));//�������
	// �������˵�
	setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
	setlinestyle(PS_SOLID, 3);//����������ϸΪ5
	setfillcolor(WHITE);//���������ɫΪ��ɫ
	fillrectangle(207, 0, 352, 70);
	settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
	settextstyle(20, 0, _T("����"));//���������СΪ30������Ϊ����
	int centerX4 = (145 - textwidth(_T("���˵�"))) / 2;
	int centerY4 = (70 - textheight(_T("���˵�"))) / 2;
	outtextxy(207 + centerX4, 0 + centerY4, _T("���˵�"));//�������
	while (1) {

		peekmessage(&msg, EX_MOUSE);// ��ȡ�����Ϣ
		if (isinarea(msg.x, msg.y, 0, 0, 145, 70)) {
			setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
			setlinestyle(PS_SOLID, 5);//����������ϸΪ5
			setfillcolor(RGB(128, 128, 128));//���������ɫΪ��ɫ
			fillrectangle(0, 0, 145, 70);
			yes = 1;
		}
		else if(isinarea(msg.x, msg.y, 207, 0, 352, 70)) 
		{
			setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
			setlinestyle(PS_SOLID, 5);//����������ϸΪ5
			setfillcolor(RGB(128, 128, 128));//���������ɫΪ��ɫ
			fillrectangle(207, 0, 352, 70);
			yes = 1;
		}
		else if (!isinarea(msg.x, msg.y, 207, 0, 352, 70)||!isinarea(msg.x, msg.y, 0, 0, 145, 70))
		{
			if (yes == 1) {
				// ����һ��
					setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
					setlinestyle(PS_SOLID, 3);//����������ϸΪ5
					setfillcolor(WHITE);//���������ɫΪ��ɫ
					fillrectangle(0, 0, 145, 70);
					settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
					settextstyle(20, 0, _T("����"));//���������СΪ30������Ϊ����
					int centerX3 = (145 - textwidth(_T("����һ��"))) / 2;
					int centerY3 = (70 - textheight(_T("����һ��"))) / 2;
					outtextxy(0 + centerX3, 0 + centerY3, _T("����һ��"));//�������
					// �������˵�
					setlinecolor(RGB(128, 128, 128));//����������ɫΪ��ɫ
					setlinestyle(PS_SOLID, 3);//����������ϸΪ5
					setfillcolor(WHITE);//���������ɫΪ��ɫ
					fillrectangle(207, 0, 352, 70);
					settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
					settextstyle(20, 0, _T("����"));//���������СΪ30������Ϊ����
					int centerX4 = (145 - textwidth(_T("���˵�"))) / 2;
					int centerY4 = (70 - textheight(_T("���˵�"))) / 2;
					outtextxy(207 + centerX4, 0 + centerY4, _T("���˵�"));//�������
				yes = 0;
			}
		}
		if (msg.message == WM_LBUTTONDBLCLK && isinarea(msg.x, msg.y, 0, 0, 145, 70)) {
			return 1;
		}
		else if (msg.message == WM_LBUTTONDBLCLK && isinarea(msg.x, msg.y, 147, 0, 290, 70)) {
			return 0;
		}
	}
}
void overselect()
{
	msg = { 0 };
	initgraph(352, 140, EX_NOCLOSE | EX_SHOWCONSOLE | EX_NOMINIMIZE | EX_DBLCLKS);//��ʼ������
	setbkcolor(WHITE);//���ñ�����ɫΪ��ɫ
	cleardevice(); 
	settextcolor(RGB(255, 0, 0));//����������ɫΪ��ɫ
	settextstyle(30, 0, _T("����"));//���������СΪ30������Ϊ����
	int centerX4 = (350 - textwidth(_T("�� | Ϸ | �� | ��"))) / 2;
	int centerY4 = (70 - textheight(_T("�� | Ϸ | �� | ��"))) / 2;
	outtextxy(0 + centerX4, 70 + centerY4, _T("�� | Ϸ | �� | ��"));//�������
	if (overmousemsg()) {
		closegraph();
		std::cout << "����һ��" << std::endl;
		gameplay();
	}
	else {
		std::cout << "�� �� ��" << std::endl;
		to_select();
	}
}	
void keymsg(block *now)
{
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		std::cout << "�ϼ�ͷ��������" << std::endl;
		rotate(now);
		isrotate = 1;
	}
	// ����¼�ͷ��
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		std::cout << "�¼�ͷ��������" << std::endl;
		vy++;
	}
	// ������ͷ��
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		std::cout << "���ͷ��������" << std::endl;
		vx--;
	}
	// ����Ҽ�ͷ��
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		std::cout << "�Ҽ�ͷ��������" << std::endl;
		vx++;
	}
	if (GetKeyState(VK_ESCAPE) & 0x8000 && GetKeyState(VK_SPACE) & 0x8000) {
		std::cout << "��Ϸ��ͣ" << std::endl;
		stop1 = 1;
	}

}
void solvekeymsg(block* now,block next) {
	if (stop1) {
		settextcolor(RGB(0, 0, 255));//����������ɫΪ�ۺ�ɫ
		settextstyle(80, 0, _T("����"));//���������СΪ30������Ϊ����
		outtextxy(100, 160, _T("�� ͣ"));
		outtextxy(100, 250, _T("�� BACK ����"));
		while (1) {
			if (GetAsyncKeyState(VK_BACK) & 0x8000 ){
				std::cout << "��Ϸ����" << std::endl;
				stop1 = 0;
				drawgameframe(next);
				break;
			}
			stop1 = 0;
			Sleep(50);
		}
		drawgameframe(next); 
		settextcolor(RGB(0, 0, 255));//����������ɫΪ�ۺ�ɫ
		settextstyle(80, 0, _T("����"));//���������СΪ30������Ϊ����
		outtextxy(80, 160, _T(" �� ��"));
		Sleep(1000);
		settextcolor(RGB(0, 0, 255));//����������ɫΪ�ۺ�ɫ
		settextstyle(80, 0, _T("����"));//���������СΪ30������Ϊ����
		outtextxy(80, 160, _T(" �� ��"));
		Sleep(1000);
		drawgameframe(next);
		settextcolor(RGB(0, 0, 255));//����������ɫΪ�ۺ�ɫ
		settextstyle(80, 0, _T("����"));//���������СΪ30������Ϊ����
		outtextxy(80, 160, _T(" һ ��"));
		drawgameframe(next);
		drawblock(*now);
		Sleep(1000);
		drawgameframe(next);
		drawgameframe(next);
	}
	if (isrotate == 1)cleanblock(btemp);
	block temp = *now;
	if (vx != 0) {
		for (int i = 0; i < 4; i++) {
			temp.smblock[i].x += vx;
		}
		vx = 0;
	}
	if (vy != 0) {
		for (int i = 0; i < vy; i++) {
			drop(&temp);
		}
		vy = 0;
	}
	if (!iscrash(temp)) {
		cleanblock(*now);
		*now = temp;
	}
	drawblock(*now);
}
////void clearFullLines() {
//	for (int n = 4;n > 0;n--) {
//		int fullLines = 0;
//		for (int i = GAME_HEIGHT - 1; i >= 0; --i) {
//			bool isFull = true;
//			for (int j = 0; j < GAME_WIDTH; ++j) {
//				if (!gameMap[i][j]) {
//					isFull = false;
//					break;
//				}
//			}
//			if (isFull) {
//				++fullLines;
//				std::cout << "����һ��" << std::endl;
//				// ��������
//				for (int k = i; k > 0; k--) {
//					for (int j = 0; j < GAME_HEIGHT; j++) {
//						gameMap[k][j] = gameMap[k - 1][j];
//					}
//				}
//				// ������һ����Ϊfalse
//				for (int j = 0; j < GAME_WIDTH; ++j) {
//					gameMap[0][j] = false;
//				}
//			}
//		}
//	}
//	// game.score += fullLines * 100; ������ÿ����һ�е�100�֣�
//}

void clearFullLines() {
	int fullLines = 0;
	// ����ÿһ��
	for (int i = GAME_HEIGHT - 1; i >= 0; --i) {
		bool isFull = true;
		// �������Ƿ�Ϊ����
		for (int j = 0; j < GAME_WIDTH; ++j) {
			if (!gameMap[i][j]) {
				isFull = false;
				break;
			}
		}
		if (isFull) {
			++fullLines;
			std::cout << "����һ��" << std::endl;
			// �������У����Ϸ�����������
			for (int k = i; k > 0; k--) {
				for (int j = 0; j < GAME_WIDTH; j++) {
					gameMap[k][j] = gameMap[k - 1][j];
				}
			}
			// ������һ����Ϊ false
			for (int j = 0; j < GAME_WIDTH; ++j) {
				gameMap[0][j] = false;
			}
			// ����һ�к󣬵�ǰ�����¼�飬��Ϊ�Ϸ������ƿ����ֲ�������
			++i;
		}
	}
	// ÿ����һ�е� 100 ��
	game.score += fullLines * 100;
}
void drawnext(block next) // ����һ��
{
	rotate(&next);
	int x[4], y[4];
	int r1 = next.img[next.typ].r1;
	int g1 = next.img[next.typ].g1;
	int b1 = next.img[next.typ].b1;
	int r2 = next.img[next.typ].r2;
	int g2 = next.img[next.typ].g2;
	int b2 = next.img[next.typ].b2;
	int X1, Y1;
	setlinecolor(RGB(r1, g1, b1));//���ñ߿���ɫ
	setfillcolor(RGB(r2, g2, b2));//���������ɫ
	X1 = (200 - ((next.smblock[0].x + next.smblock[3].x) * 30)) / 2 + 320;
	Y1 = (150 - ((next.smblock[0].y + next.smblock[3].y) * 30)) / 2 + 170;
	for (int i = 0; i < 4; i++) {    
		x[i] = next.smblock[i].x * 30 + X1;
		y[i] = next.smblock[i].y * 30 + Y1;
	}
	setlinestyle(PS_SOLID, 1);//�����������Ϊʵ��
	for (int i = 0; i < 4; i++) {
		fillrectangle(x[i], y[i], x[i] + 30, y[i] + 30);
	}

}