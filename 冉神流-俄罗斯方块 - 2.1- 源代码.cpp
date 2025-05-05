#include<iostream>
#include<string>
#include<windows.h>
#include<easyx.h>
#include<cstdlib>
#include<ctime>
#include <conio.h>
#include<random>
#include<fstream>
#define pxsize 10

void AAA_update_note()
{
	std::cout << "代码来自 -- 春霁柟 俄罗斯方块 v2.1" << std::endl;
	std::cout << "2.1更新日志：" << std::endl;
	std::cout << "1、添加了 setting 保存键" << std::endl;
	std::cout << "2、更新了setting 界面" << std::endl;
	std::cout << "3、更新了 help 界面" << std::endl;
	std::cout << "4、更新了游戏最高分数功能" << std::endl;
	std::cout << "为小瑜考虑改成单击进入选项" << std::endl;
	std::cout << "本次更新于：2025年5月5号" << std::endl;
}
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
int havesettingbg;

class point {
public:
	int x, y; // 行 列
};
struct bkcolor{
	int r1, g1, b1; // 边框颜色
	int r2, g2, b2; // 填充颜色
};
class block {
public:
	block() {
		// 使用当前时间作为随机数种子
			// 创建一个随机数引擎
		std::random_device rd;
		std::mt19937 gen(rd());

		// 创建一个均匀分布，范围在0到6之间
		std::uniform_int_distribution<> dis(0, 6);
		std::uniform_int_distribution<> rot(0, 4);
		typ = dis(gen);
		rota = rot(gen);
		// 生成范围在 1 到 7 之间的随机数
		for (int i = 0; i < 4; i++) {
			smblock[i].x = blocks[typ][i] % 2 + 5;
			smblock[i].y = blocks[typ][i] / 2;
		}

	}
public:
	int typ;
	int rota;
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
{255, 215, 0, 255, 255, 0} 
};

void recordscore(); // 记录分数
int readscore(); // 显示最高分数
class GameMessage {
public:
	int score;
	int speed;
	int difficulty;
	int lastscore;
	GameMessage() {
		score = 0;
		speed = 1;
		difficulty = 1;
		lastscore = readscore();
	}
};
// 代码来自  春霁柟 \(^v^)/
void drawnext(block next); // 画下一个
void showwelcome(); // 显示欢迎界面
void solvekeymsg(block* now, block next);
void showgamesetting();
// 游戏难度不同
void easy_difficulty(block& now);
void normal_difficulty(block &now);
void hard_difficulty(block& now);
void hell_difficulty(block& now);

bool isgameover(); // 判断游戏是否结束
void cleanblock(block now) {
	int x[4], y[4];
	for (int i = 0; i < 4; i++) {
		x[i] = now.smblock[i].x * 20 + begin_x;
		y[i] = now.smblock[i].y * 20 + begin_y;
	}
	setlinecolor(getbkcolor());//设置边框颜色
	setfillcolor(getbkcolor());//设置填充颜色
	setlinestyle(PS_SOLID, 2);//设置线条风格为实线
	for (int i = 0; i < 4; i++) {
		fillrectangle(x[i], y[i], x[i] + 20, y[i] + 20);
	}
}
int mousemsg_to_select(); // 鼠标消息
void mousemsg_setting();
bool isinarea(int mx, int my, int x1, int y1, int x2, int y2);	// 判断鼠标是否在区域内
void to_select(); // 选择
void gameplay(); // 游戏界面
void gamesetting(); // 游戏设置
void gamehelp(); // 游戏帮助
void gameexit(); // 退出游戏
void keymsg(block *now); // 键盘消息
void drop(block* nblock); // 下落
void rotate(block* nblock); // 旋转
// 画方块
void drawblock(block nblock);
void drawallframe(int x1, int y1);
// 计分
int overmousemsg();
void score();
void drawgameframe(block next);// 画游戏框架
ExMessage msg = { 0 };
ExMessage msgkey = { 0 };
int main()
{
	// 创建一个随机数引擎
	std::random_device rd;
	std::mt19937 gen(rd());
	// 创建一个均匀分布，范围在1到100之间
	std::uniform_int_distribution<> dis(1, 100);
	AAA_update_note();
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
	settextcolor(RGB(231, 113, 215));//设置字体颜色为超级好看的粉红色
	settextstyle(50, 0, _T("黑体"));//设置字体大小为50，字体为黑体
	drawallframe(x, y);
	int centerX = (x - textwidth(_T("欢 迎 游 玩 俄 罗 斯 方 块 喵 (-ω-) /"))) / 2;
	outtextxy(centerX, 70, _T("欢 迎 游 玩 俄 罗 斯 方 块 喵 (-ω-）/"));//输出文字
	// 画 方 框 实线 虚线 实线
	//setlinestyle(PS_SOLID, 8);//设置线条风格为实线
	//setlinecolor(RGB(253, 208, 222));//设置线条颜色为粉红色 但是好浅
	//line(6, 10, 1195, 10);
	//line(6, 645, 1195, 645);
	//line(6, 10, 6, 645);
	//line(1195, 10, 1195, 645);
	//setlinestyle(PS_DASH, 5);//设置线条风格为虚线
	//setlinecolor(RGB(71, 166, 74));//设置线条颜色为绿色
	//line(14, 18, 1187, 18);	
	//line(14, 637, 1187, 637);
	//line(14, 18, 14, 637);
	//line(1187, 18, 1187, 637);
	//setlinestyle(PS_SOLID, 8);//设置线条风格为实线
	//setlinecolor(RGB(253, 208, 222));//设置线条颜色为粉红色 但是好浅
	//line(22, 26, 1179, 22);
	//line(22, 629, 1179, 629);
	//line(22, 26, 22, 629);
	//line(1179, 26, 1179, 629);
	// 画一下俄罗斯方块 的形状
	// 内裤型 我最爱 所以要粉红色的
	setlinecolor(RGB(239, 125, 200));//设置边框颜色为粉红色
	setlinestyle(PS_SOLID ,3);//设置线条粗细为5
	setfillcolor(RGB(253, 208, 222));//设置填充颜色为粉红色
	fillrectangle(120, 240, 160, 280);
	fillrectangle(80, 200, 120, 240);
	fillrectangle(120, 200, 160, 240);
	fillrectangle(160, 200, 200, 240);
	// 长条 是我等不到的 蓝色的 躺在最下面吧。。。。。
	setlinecolor(RGB(100, 100, 208));//设置边框颜色为蓝色
	setlinestyle(PS_SOLID, 3);//设置线条粗细为3
	setfillcolor(RGB(135, 206, 235));//设置填充颜色为天蓝色
	fillrectangle(160, 500, 200, 540);
	fillrectangle(200, 500, 240, 540);
	fillrectangle(240, 500, 280, 540);
	fillrectangle(280, 500, 320, 540);
	// 田字型  绿色的
	setlinecolor(RGB(0, 128, 0));//设置边框颜色为深绿色
	setlinestyle(PS_SOLID, 3);//设置线条粗细为3
	setfillcolor(RGB(0, 255, 0));//设置填充颜色为浅绿色
	fillrectangle(100, 360, 140, 400);
	fillrectangle(140, 360, 180, 400);
	fillrectangle(100, 400, 140, 440);
	fillrectangle(140, 400, 180, 440);
	// 7字型 很难受 褐色的
	setlinecolor(RGB(139, 69, 19));//设置边框颜色为褐色
	setlinestyle(PS_SOLID, 3);//设置线条粗细为3
	setfillcolor(RGB(210, 105, 30));//设置填充颜色为巧克力色
	fillrectangle(280, 240, 320, 280);
	fillrectangle(320, 240, 360, 280);
	fillrectangle(360, 240, 400, 280);
	fillrectangle(360, 200, 400, 240);
	
	//  Z 字型 很讨厌！！ 黄色的
	setlinecolor(RGB(255, 215, 0));//设置边框颜色为金黄色
	setlinestyle(PS_SOLID, 3);//设置线条粗细为3
	setfillcolor(RGB(255, 255, 0));//设置填充颜色为黄色
	fillrectangle(360, 400, 400, 440);
	fillrectangle(280, 360, 320, 400);
	fillrectangle(320, 360, 360, 400);
	fillrectangle(320, 400, 360, 440);
	// 分割线  右边输出菜单
	setlinecolor(RGB(201, 151, 242));//设置线条颜色为紫色
	setlinestyle(PS_SOLID, 8);//设置线条风格为实线
	line(500, 170, 500, 620);
	// 输出菜单
	settextcolor(RGB(210, 105, 30));//设置字体颜色为巧克力色
	settextstyle(50, 0, _T("粗黑体"));//设置字体大小为50，字体为黑体
	int centermX1 = (1200 - 500 - textwidth(_T("游 戏 菜 单"))) / 2;
	outtextxy(500 + centermX1, 200, _T("游 戏 菜 单"));//输出文字


	//1.开始游 绘制灰色边框
	setlinecolor(RGB(128, 128, 128));//设置线条颜色为灰色
	setlinestyle(PS_SOLID, 5);//设置线条粗细为5
	setfillcolor(WHITE);//设置填充颜色为白色
	fillrectangle(600, 300, 800, 350);
	settextcolor(RGB(255, 0, 0));//设置字体颜色为红色
	settextstyle(30, 0, _T("黑体"));//设置字体大小为30，字体为黑体
	int centerX1 = (200 - textwidth(_T("开始游戏"))) / 2;
	int centerY1 = (50 - textheight(_T("开始游戏"))) / 2;
	outtextxy(600 + centerX1, 300 + centerY1, _T("开始游戏"));//输出文字
	//2.游戏设置
	setlinecolor(RGB(128, 128, 128));//设置线条颜色为灰色
	setlinestyle(PS_SOLID, 5);//设置线条粗细为5
	setfillcolor(WHITE);//设置填充颜色为白色
	fillrectangle(600, 450, 800, 500);
	settextcolor(RGB(255, 0, 0));//设置字体颜色为红色
	settextstyle(30, 0, _T("黑体"));//设置字体大小为30，字体为黑体
	int centerX2 = (200 - textwidth(_T("游戏设置"))) / 2;
	int centerY2 = (50 - textheight(_T("游戏设置"))) / 2;
	outtextxy(600 + centerX2, 450 + centerY2, _T("游戏设置"));//输出文字
	//3.游戏帮助
	setlinecolor(RGB(128, 128, 128));//设置线条颜色为灰色
	setlinestyle(PS_SOLID, 5);//设置线条粗细为5
	setfillcolor(WHITE);//设置填充颜色为白色
	fillrectangle(890, 300, 1090, 350);
	settextcolor(RGB(255, 0, 0));//设置字体颜色为红色
	settextstyle(30, 0, _T("黑体"));//设置字体大小为30，字体为黑体
	int centerX3 = (200 - textwidth(_T("游戏帮助"))) / 2;
	int centerY3 = (50 - textheight(_T("游戏帮助"))) / 2;
	outtextxy(890 + centerX3, 300 + centerY3, _T("游戏帮助"));//输出文字
	
	//4.退出游戏
	setlinecolor(RGB(128, 128, 128));//设置线条颜色为灰色
	setlinestyle(PS_SOLID, 5);//设置线条粗细为5
	setfillcolor(WHITE);//设置填充颜色为白色
	fillrectangle(890, 450, 1090, 500);
	settextcolor(RGB(255, 0, 0));//设置字体颜色为红色
	settextstyle(30, 0, _T("黑体"));//设置字体大小为30，字体为黑体
	int centerX4 = (200 - textwidth(_T("退出游戏"))) / 2;
	int centerY4 = (50 - textheight(_T("退出游戏"))) / 2;
	outtextxy(890 + centerX4, 450 + centerY4, _T("退出游戏"));//输出文字

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

	initgraph(1200, 650, EX_NOCLOSE | EX_SHOWCONSOLE | EX_NOMINIMIZE | EX_DBLCLKS);//初始化窗口
	//setbkcolor(RGB(231, 113, 215));//设置背景颜色为粉红色 诶嘿 算了 粉红色看的我快瞎了
	setbkcolor(WHITE);//设置背景颜色为白色 比较不瞎眼
	cleardevice(); // 清屏
	showwelcome();
	peekmessage(&msg, EX_MOUSE);// 获取鼠标消息
	int mode = -1;
	mode = mousemsg_to_select();
	switch (mode)
		{
		case 1:
		{
			// 开始游戏
			{
				mode = -1;
				
				std::cout << "选择模式：开始游戏 代码来自春霁柟" << std::endl;
				for (int i = 0;i < GAME_HEIGHT + 1;i++)
				{
					for (int j = 0;j < GAME_WIDTH + 1;j++)
					{
						gameMap[i][j] = false;
					}
				}
				closegraph();
				gameplay();
			}
			break;
		}
		case 2:
		{
			// 游戏设置
			{
				mode = -1;
				std::cout << "用户选择：游戏设置" << std::endl;
				cleardevice();
				gamesetting();
			}
			break;
		}
		case 3:
		{
			// 游戏帮助
			{
				mode = -1;
				std::cout << "用户选择：游戏帮助" << std::endl;
				closegraph();
				gamehelp();
			}
			break;
		}
		case 4:
		{
			{
				mode = -1;
				// 退出游戏
				gameexit();
				break;
			}
		}
	}
}
// x1 x2 y1 y2 长方形的坐标 n 是距离 m 是长度 k 是粗细
void drawmsg_to_select(int x1, int y1, int x2, int y2, int n, int m, int k)
{
	x1 -= n;
	x2 += n;
	y1 -= n;
	y2 += n;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, k);
	line(x1, y1, x1 + m, y1);
	line(x1, y1, x1, y1 + m);
	line(x1, y2, x1 + m, y2);
	line(x1, y2, x1, y2 - m);
	line(x2, y1, x2 - m, y1);
	line(x2, y1, x2, y1 + m);
	line(x2, y2, x2 - m, y2);
	line(x2, y2, x2, y2 - m);
}
// x1 x2 y1 y2 长方形的坐标 n 是距离 m 是长度 k 是粗细
void undo_drawmsg_to_select(int x1, int y1, int x2, int y2, int n, int m, int k)
{
	x1 -= n;
	x2 += n;
	y1 -= n;
	y2 += n;
	setlinecolor(getbkcolor());
	setlinestyle(PS_SOLID, k);
	line(x1, y1, x1 + m, y1);
	line(x1, y1, x1, y1 + m);
	line(x1, y2, x1 + m, y2);
	line(x1, y2, x1, y2 - m);
	line(x2, y1, x2 - m, y1);
	line(x2, y1, x2, y1 + m);
	line(x2, y2, x2 - m, y2);
	line(x2, y2, x2, y2 - m);
}
int mousemsg_to_select()
{
	int yes = 0;
	while (1) {
		
		peekmessage(&msg, EX_MOUSE);// 获取鼠标消息
		if (isinarea(msg.x, msg.y, 600, 300, 800, 350) && yes == 0) {
			drawmsg_to_select(600, 300, 800, 350, 10, 15, 5);
			yes = 1;	
		}
		else if (isinarea(msg.x, msg.y, 600, 450, 800, 500) && yes == 0) {
			drawmsg_to_select(600, 450, 800, 500, 10, 15, 5);
			yes = 1;	
		}
		else if (isinarea(msg.x, msg.y, 890, 300, 1090, 350) && yes == 0) {
			drawmsg_to_select(890, 300, 1090, 350, 10, 15, 5);
			yes = 1;
		}
		else if (isinarea(msg.x, msg.y, 890, 450, 1090, 500) && yes == 0) {
			drawmsg_to_select(890, 450, 1090, 500, 10, 15, 5);
			yes = 1;
		}
		else if (!isinarea(msg.x, msg.y, 600, 300, 800, 350) && !isinarea(msg.x, msg.y, 600, 450, 800, 500) && !isinarea(msg.x, msg.y, 890, 300, 1090, 350) && !isinarea(msg.x, msg.y, 890, 450, 1090, 500))
		{
			if (yes == 1) {
				undo_drawmsg_to_select(600, 300, 800, 350, 10, 15, 5);
				undo_drawmsg_to_select(600, 450, 800, 500, 10, 15, 5);
				undo_drawmsg_to_select(890, 300, 1090, 350, 10, 15, 5);
				undo_drawmsg_to_select(890, 450, 1090, 500, 10, 15, 5);
				yes = 0;
			}
		}
		if (msg.message == WM_LBUTTONUP && isinarea(msg.x, msg.y, 600, 300, 800, 350)) {
			return 1;
		}
		else if (msg.message == WM_LBUTTONUP && isinarea(msg.x, msg.y, 600, 450, 800, 500)) {
			return 2;
		}
		else if (msg.message == WM_LBUTTONUP && isinarea(msg.x, msg.y, 890, 300, 1090, 350)) {
			return 3;
		}
		else if (msg.message == WM_LBUTTONUP && isinarea(msg.x, msg.y, 890, 450, 1090, 500)) {
			return 4;
		}
	}
}
void overselect();
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
	initgraph(600, 800, EX_NOCLOSE | EX_SHOWCONSOLE | EX_NOMINIMIZE | EX_DBLCLKS);//初始化游戏窗口
	setbkcolor(WHITE);//设置背景颜色为白色
	game.score = 0;
	game.speed = 1;
	block now;
	game.lastscore = readscore();
	Sleep(1000);
	switch (game.difficulty)
	{
	case 0:
		easy_difficulty(now);
	case 1:
		normal_difficulty(now);
	case 2:
		hard_difficulty(now);
	case 3:
		hell_difficulty(now);
	}
}
void easy_difficulty(block& now)
{
	int havedeadline = 0;
	while (1) { // 游戏循环
		haveground = 0;
		block next;
		drawgameframe(next); // 画游戏框架
		if (havedeadline != 3) {
			setlinecolor(RED);//设置线条颜色为红色
			setlinestyle(PS_DOT, 5);//设置线条风格为虚线
			line(52, 150, 300, 148);
			havedeadline += 1;
		}
		while (1) // 方块下落 循环
		{
			// 判断是否到底
			if (iscrash(now)) {
				havedeadline = 0;
				landBlock(now);
				std::cout << "方块落地" << std::endl;
				if (isgameover()) {
					std::cout << "游戏结束" << std::endl;
					for (int k = 0; k < 19; k++) {
						for (int j = 0; j < 12; j++) {
							gameMap[k][j] = false;
						}
					}
					overselect();
				}
				for (int i = 0; i < 4; i++) {
					std::cout << "方块到底了" << "X:" << now.smblock[i].x << "Y:" << now.smblock[i].y << std::endl;
				}
				break;
			}
			keymsg(&now); // 键盘操作
			Sleep(70);
			solvekeymsg(&now, next);
			keymsg(&now); // 键盘操作
			Sleep(70);
			solvekeymsg(&now, next);
			keymsg(&now); // 键盘操作
			Sleep(70);
			solvekeymsg(&now, next);
			keymsg(&now); // 键盘操作
			Sleep(70);
			solvekeymsg(&now, next);
			keymsg(&now);
			Sleep(70);
			solvekeymsg(&now, next);
			keymsg(&now);
			Sleep(70);
			solvekeymsg(&now, next);
			cleanblock(now);
			drop(&now); // 下落
			if (havedeadline != 3) {
				setlinecolor(RED);//设置线条颜色为红色
				setlinestyle(PS_DOT, 5);//设置线条风格为虚线
				line(52, 150, 300, 148);
				havedeadline += 1;
			}
			drawblock(now); // 画方块
			haveground = 0;
			//drawgameframe(game, next); // 画游戏框架
			std::cout << "方块下落" << std::endl;
			// 画方块
		}
		// 选取中心点（这里选择第二个方块作为中心点）
		point center = next.smblock[1];
		for (int i = 0;i < next.rota;i++)
		{
			for (int i = 0; i < 4; i++) {
				int dx = next.smblock[i].x - center.x;
				int dy = next.smblock[i].y - center.y;
				next.smblock[i].x = center.x - dy;
				next.smblock[i].y = center.y + dx;
			}
		}
		now = next;
	}
}
void normal_difficulty(block &now)
{
	int havedeadline = 0;
	while (1) { // 游戏循环
		haveground = 0;
		block next;
		drawgameframe(next); // 画游戏框架
		if (havedeadline != 3) {
			setlinecolor(RED);//设置线条颜色为红色
			setlinestyle(PS_DOT, 5);//设置线条风格为虚线
			line(52, 150, 300, 148);
			havedeadline += 1;
		}
		while (1) // 方块下落 循环
		{
			// 判断是否到底
			if (iscrash(now)) {
				havedeadline = 0;
				landBlock(now);
				std::cout << "方块落地" << std::endl;
				if (isgameover()) {
					std::cout << "游戏结束" << std::endl;
					for (int k = 0; k < 19; k++) {
						for (int j = 0; j < 12; j++) {
							gameMap[k][j] = false;
						}
					}
					overselect();
				}
				for (int i = 0; i < 4; i++) {
					std::cout << "方块到底了" << "X:" << now.smblock[i].x << "Y:" << now.smblock[i].y << std::endl;
				}
				break;
			}
			keymsg(&now); // 键盘操作
			Sleep(75);
			solvekeymsg(&now, next);
			keymsg(&now);
			Sleep(75);
			solvekeymsg(&now, next);
			keymsg(&now);
			Sleep(75);
			solvekeymsg(&now, next);
			keymsg(&now);
			Sleep(75);
			solvekeymsg(&now, next);
			cleanblock(now);
			drop(&now); // 下落
			if (havedeadline != 3) {
				setlinecolor(RED);//设置线条颜色为红色
				setlinestyle(PS_DOT, 5);//设置线条风格为虚线
				line(52, 150, 300, 148);
				havedeadline += 1;
			}
			drawblock(now); // 画方块
			haveground = 0;
			//drawgameframe(game, next); // 画游戏框架
			std::cout << "方块下落" << std::endl;
			// 画方块
		}
		// 选取中心点（这里选择第二个方块作为中心点）
		point center = next.smblock[1];
		for (int i = 0;i < next.rota;i++)
		{
			for (int i = 0; i < 4; i++) {
				int dx = next.smblock[i].x - center.x;
				int dy = next.smblock[i].y - center.y;
				next.smblock[i].x = center.x - dy;
				next.smblock[i].y = center.y + dx;
			}
		}
		now = next;
	}
}
void hard_difficulty(block& now)
{
	int havedeadline = 0;
	while (1) { // 游戏循环
		haveground = 0;
		block next;
		drawgameframe(next); // 画游戏框架
		if (havedeadline != 3) {
			setlinecolor(RED);//设置线条颜色为红色
			setlinestyle(PS_DOT, 5);//设置线条风格为虚线
			line(52, 150, 300, 148);
			havedeadline += 1;
		}
		while (1) // 方块下落 循环
		{
			// 判断是否到底
			if (iscrash(now)) {
				havedeadline = 0;
				landBlock(now);
				std::cout << "方块落地" << std::endl;
				if (isgameover()) {
					std::cout << "游戏结束" << std::endl;
					for (int k = 0; k < 19; k++) {
						for (int j = 0; j < 12; j++) {
							gameMap[k][j] = false;
						}
					}
					overselect();
				}
				for (int i = 0; i < 4; i++) {
					std::cout << "方块到底了" << "X:" << now.smblock[i].x << "Y:" << now.smblock[i].y << std::endl;
				}
				break;
			}
			keymsg(&now);
			Sleep(55);
			solvekeymsg(&now, next);
			keymsg(&now);
			Sleep(55);
			solvekeymsg(&now, next);
			keymsg(&now);
			Sleep(55);
			solvekeymsg(&now, next);
			cleanblock(now);
			drop(&now); // 下落
			if (havedeadline != 3) {
				setlinecolor(RED);//设置线条颜色为红色
				setlinestyle(PS_DOT, 5);//设置线条风格为虚线
				line(52, 150, 300, 148);
				havedeadline += 1;
			}
			drawblock(now); // 画方块
			haveground = 0;
			//drawgameframe(game, next); // 画游戏框架
			std::cout << "方块下落" << std::endl;
			// 画方块
		}
		// 选取中心点（这里选择第二个方块作为中心点）
		point center = next.smblock[1];
		for (int i = 0;i < next.rota;i++)
		{
			for (int i = 0; i < 4; i++) {
				int dx = next.smblock[i].x - center.x;
				int dy = next.smblock[i].y - center.y;
				next.smblock[i].x = center.x - dy;
				next.smblock[i].y = center.y + dx;
			}
		}
		now = next;
	}
}
void hell_difficulty(block& now)
{
	int havedeadline = 0;
	while (1) { // 游戏循环
		haveground = 0;
		block next;
		drawgameframe(next); // 画游戏框架
		if (havedeadline != 3) {
			setlinecolor(RED);//设置线条颜色为红色
			setlinestyle(PS_DOT, 5);//设置线条风格为虚线
			line(52, 150, 300, 148);
			havedeadline += 1;
		}
		while (1) // 方块下落 循环
		{
			// 判断是否到底
			if (iscrash(now)) {
				havedeadline = 0;
				landBlock(now);
				std::cout << "方块落地" << std::endl;
				if (isgameover()) {
					std::cout << "游戏结束" << std::endl;
					for (int k = 0; k < 19; k++) {
						for (int j = 0; j < 12; j++) {
							gameMap[k][j] = false;
						}
					}
					overselect();
				}
				for (int i = 0; i < 4; i++) {
					std::cout << "方块到底了" << "X:" << now.smblock[i].x << "Y:" << now.smblock[i].y << std::endl;
				}
				break;
			}
			keymsg(&now);
			Sleep(60);
			solvekeymsg(&now, next);
			//keymsg(&now);
			//Sleep(55);
			//solvekeymsg(&now, next);
			cleanblock(now);
			drop(&now); // 下落
			if (havedeadline != 3) {
				setlinecolor(RED);//设置线条颜色为红色
				setlinestyle(PS_DOT, 5);//设置线条风格为虚线
				line(52, 150, 300, 148);
				havedeadline += 1;
			}
			drawblock(now); // 画方块
			haveground = 0;
			//drawgameframe(game, next); // 画游戏框架
			std::cout << "方块下落" << std::endl;
			// 画方块
		}
		// 选取中心点（这里选择第二个方块作为中心点）
		point center = next.smblock[1];
		for (int i = 0;i < next.rota;i++)
		{
			for (int i = 0; i < 4; i++) {
				int dx = next.smblock[i].x - center.x;
				int dy = next.smblock[i].y - center.y;
				next.smblock[i].x = center.x - dy;
				next.smblock[i].y = center.y + dx;
			}
		}
		now = next;
	}
}
void showgamesetting()
{
	int centerX1;
	int centerY1;
	if (!havesettingbg) {
		initgraph(800, 600, EX_NOCLOSE | EX_SHOWCONSOLE | EX_NOMINIMIZE | EX_DBLCLKS);
		setbkcolor(WHITE);//设置背景颜色为白色 比较不瞎眼
		cleardevice(); // 清屏
		setlinestyle(PS_SOLID, 5);//设置线条风格为实线
		setlinecolor(RGB(253, 208, 222));//设置线条颜色为粉红色 但是好浅
		fillrectangle(5, 5, 795, 595);
		setlinestyle(PS_DASH, 5);//设置线条风格为虚线
		setlinecolor(RGB(71, 166, 74));//设置线条颜色为绿色
		fillrectangle(12, 12, 788, 588);
		setlinestyle(PS_SOLID, 5);//设置线条风格为实线
		setlinecolor(RGB(253, 208, 222));//设置线条颜色为粉红色 但是好浅
		fillrectangle(19, 19, 781, 581);
		settextcolor(RGB(231, 113, 215));//设置字体颜色为粉红色
		settextstyle(40, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		centerX1 = (800 - textwidth(_T("俄罗斯方快设置"))) / 2;
		centerY1 = (120 - textheight(_T("俄罗斯方块设置"))) / 2;
		outtextxy(centerX1, centerY1, _T("俄罗斯方块设置"));
		settextcolor(RGB(231, 113, 215));//设置字体颜色为粉红色
		line(19, 100, 781, 100);
		setlinecolor(BLACK);//设置线条颜色为粉红色 但是好浅
		settextstyle(40, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		setlinestyle(PS_SOLID, 2);//设置线条风格为实线
		fillrectangle(310, 145, 430, 195);
		outtextxy(40, 150, _T("难度选择"));
		setlinecolor(RGB(200, 200, 200));//设置线条颜色为粉红色 但是好浅
		setfillcolor(RGB(200, 200, 200));
		fillrectangle(240, 155, 290, 185);
		setlinecolor(RGB(160, 160, 160));
		fillrectangle(250, 165, 280, 175);
		setlinecolor(RGB(200, 200, 200));//设置线条颜色为粉红色 但是好浅
		setfillcolor(RGB(200, 200, 200));
		fillrectangle(450, 155, 500, 185);
		setlinecolor(RGB(160, 160, 160));
		fillrectangle(460, 165, 490, 175);
		setlinecolor(BLACK);
		settextstyle(35, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		centerX1 = (120 - textwidth(_T("主菜单"))) / 2;
		centerY1 = (40 - textheight(_T("主菜单"))) / 2;
		setfillcolor(RGB(253, 208, 222));
		fillrectangle(340, 500, 460, 540);
		setbkmode(TRANSPARENT);
		outtextxy(centerX1 + 340, centerY1 + 500, _T("主菜单"));
		Sleep(50);
		setbkmode(OPAQUE);
	}
	setbkmode(OPAQUE);
	settextstyle(30, 0, _T("黑体"));//设置字体大小为30，字体为黑体
	centerX1 = (120 - textwidth(_T("简单"))) / 2;
	centerY1 = (50 - textheight(_T("简单"))) / 2;
	switch (game.difficulty)
	{
	case 0:
	{
		settextcolor(RGB(0, 255, 0));//设置字体颜色为粉红色
		outtextxy(centerX1 + 310, centerY1 + 145, _T("简单"));
	}
	break;
	case 1:
	{
		settextcolor(RGB(0, 0, 255));//设置字体颜色为粉红色
		outtextxy(centerX1 + 310, centerY1 + 145, _T("普通"));
	}
	break;
	case 2:
	{
		settextcolor(RGB(232, 176, 33));//设置字体颜色为粉红色
		outtextxy(centerX1 + 310, centerY1 + 145, _T("困难"));
	}
	break;
	case 3:
	{
		settextcolor(RGB(139, 0, 0));//设置字体颜色为粉红色
		outtextxy(centerX1 + 310, centerY1 + 145, _T("地狱"));
	}
	break;
	}
}
void gamesetting()
{
	havesettingbg = 0;
	while (1) {
		Sleep(588);
		if (!havesettingbg)
		{
			showgamesetting();
			havesettingbg = 1;
		}
		mousemsg_setting();
		game.difficulty = (game.difficulty + 4) % 4;
		showgamesetting();
	}
	to_select();
}
void gamehelp()
{
	initgraph(800, 600, EX_NOCLOSE | EX_SHOWCONSOLE | EX_NOMINIMIZE | EX_DBLCLKS);
	setbkcolor(WHITE);//设置背景颜色为白色 比较不瞎眼
	cleardevice(); // 清屏
	drawallframe(800, 600);
	settextcolor(RGB(0, 255, 255));
	settextstyle(50, 0, _T("黑体"));//设置字体大小为30，字体为黑体
	int centerX1 = (800 - textwidth(_T("游戏帮助"))) / 2;
	int centerY1 = (100 - textheight(_T("游戏帮助"))) / 2;
	outtextxy(centerX1, centerY1, _T("游戏帮助"));
	setlinecolor(RGB(253, 208, 222));//设置线条颜色为粉红色
	setlinestyle(PS_SOLID, 5);//设置线条风格为实线
	line(0, 100, 800, 100);
	settextcolor(RGB(0, 0, 255));//设置字体颜色为粉红色
	settextstyle(40, 0, _T("黑体"));//设置字体大小为30，字体为黑体
	int x1 = 180;
	int y1 = 200;
	outtextxy(x1, y1, _T("上---旋转"));
	outtextxy(x1 + 240, y1, _T("下---下移"));
	outtextxy(x1, y1 + 150, _T("左---左移"));
	outtextxy(x1 + 240, y1 + 150, _T("右---上移"));
	setlinecolor(RGB(128, 128, 128));//设置线条颜色为灰色
	setlinestyle(PS_SOLID, 5);//设置线条粗细为5
	setfillcolor(WHITE);//设置填充颜色为白色
	fillrectangle(300, 500, 500, 550);
	settextcolor(RGB(255, 0, 0));//设置字体颜色为红色
	settextstyle(30, 0, _T("黑体"));//设置字体大小为30，字体为黑体
	centerX1 = (200 - textwidth(_T("主菜单"))) / 2;
	centerY1 = (50 - textheight(_T("主菜单"))) / 2;
	outtextxy(300 + centerX1, 500 + centerY1, _T("主菜单"));//输出文字
	int yes2 = 0;
	peekmessage(&msg, EX_MOUSE);// 获取鼠标消息
	while (1) {
		peekmessage(&msg, EX_MOUSE);// 获取鼠标消息
		if (yes2 == 1 && isinarea(msg.x, msg.y, 300, 500, 500, 550))
		{
			drawmsg_to_select(300, 500, 500, 550, 10, 20, 4);
			yes2 = 0;
		}
		if (yes2 == 0 && !isinarea(msg.x, msg.y, 300, 500, 500, 550))
		{
			undo_drawmsg_to_select(300, 500, 500, 550, 10, 20, 4);
			yes2 = 1;
		}
		if (msg.message == WM_LBUTTONUP && isinarea(msg.x, msg.y, 300, 500, 500, 550)) {
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
	setlinecolor(RGB(r1, g1, b1));//设置边框颜色
	setfillcolor(RGB(r2, g2, b2));//设置填充颜色
	setlinestyle(PS_SOLID, 2);//设置线条风格为实线
	for (int i = 0; i < 4; i++) {
		fillrectangle(x[i], y[i], x[i] + 20, y[i] + 20);
	}
}
void drawgameframe(block next)
{
	// 画游戏框架
	if (!haveground) {
		setbkcolor(WHITE);
		// 一块白色的矩形为背景
		setfillcolor(WHITE);
		setlinecolor(WHITE);
		solidrectangle(0, 0, 600, 800);
		setlinestyle(PS_SOLID, 5);//设置线条风格为实线
		cleardevice();//清屏
		drawallframe(600, 800);
		//setlinecolor(RGB(253, 208, 222));//设置线条颜色为粉红色
		//setlinestyle(PS_SOLID, 5);//设置线条风格为实线
		//line(6, 10, 595, 10);
		//line(6, 795, 595, 795);
		//line(6, 10, 6, 795);
		//line(595, 10, 595, 795);
		//setlinestyle(PS_DASH, 5);//设置线条风格为虚线
		//setlinecolor(RGB(71, 166, 74));//设置线条颜色为绿色
		//line(14, 18, 585, 18);
		//line(14, 787, 585, 787);
		//line(14, 18, 14, 787);
		//line(585, 18, 585, 787);
		//setlinecolor(RGB(253, 208, 222));//设置线条颜色为粉红色
		//setlinestyle(PS_SOLID, 5);//设置线条风格为实线
		//line(22, 26, 575, 26);
		//line(22, 779, 575, 779);
		//line(575, 26, 575, 779);
		//line(22, 26, 22, 779);
		// 方块下落的区域 黑色实线
		setlinecolor(BLACK);//设置线条颜色为黑色
		setlinestyle(PS_SOLID, 5);//设置线条风格为实线
		line(46, 130, 46, 513);
		line(46, 513, 293, 513);
		line(293, 513, 293, 130);
		//setlinecolor(RED);//设置线条颜色为红色
		//setlinestyle(PS_DOT, 5);//设置线条风格为虚线
		//line(52, 150, 300, 150);
		// 画上一次的最高分数
		settextcolor(RGB(231, 113, 215));//设置字体颜色为粉红色
		settextstyle(30, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		outtextxy(80, 30, _T("最高分："));
		std::string temps = std::to_string(readscore());
		std::wstring wideStr = std::wstring(temps.begin(), temps.end());
		outtextxy(190, 32, wideStr.c_str());
		// 画分数
		settextcolor(RGB(231, 113, 215));//设置字体颜色为粉红色
		settextstyle(30, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		outtextxy(80, 70, _T("分数："));
		temps = std::to_string(game.score);
		wideStr = std::wstring(temps.begin(), temps.end());
		outtextxy(160, 72, wideStr.c_str());
		// 画下一个
		settextcolor(RGB(0, 0, 255));//设置字体颜色为粉红色
		settextstyle(30, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		outtextxy(370, 160, _T("下 一 个"));
		setlinecolor(BLACK); //设置线条颜色为黑色
		setlinestyle(PS_SOLID, 4);//设置线条风格为虚线
		rectangle(350, 150, 550, 300);
		line(350, 200, 550, 200);
		drawnext(next);
		drawline();
		settextcolor(RGB(231, 113, 215));//设置字体颜色为粉红色
		settextstyle(28, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		outtextxy(60, 600, _T("ESC + SPACE ---- 暂停"));
		settextcolor(RGB(231, 113, 215));//设置字体颜色为粉红色
		settextstyle(28, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		outtextxy(58, 650, _T("暂停后按 ESC 返回主菜单"));
		settextcolor(RGB(51, 204, 153));//设置字体颜色为粉红色
		settextstyle(28, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		outtextxy(355, 310, _T("难度模式："));
		setlinecolor(BLACK); //设置线条颜色为黑色
		setlinestyle(PS_SOLID, 4);//设置线条风格为虚线
		rectangle(350, 300, 550, 350);
		int centerX1 = 490;
		int centerY1 = 310;
		switch (game.difficulty)
		{
		case 0:
		{
			settextcolor(RGB(0, 255, 0));//设置字体颜色为粉红色
			outtextxy(centerX1 , centerY1 , _T("简单"));
		}
		break;
		case 1:
		{
			settextcolor(RGB(0, 0, 255));//设置字体颜色为粉红色
			outtextxy(centerX1 , centerY1 , _T("普通"));
		}
		break;
		case 2:
		{
			settextcolor(RGB(232, 176, 33));//设置字体颜色为粉红色
			outtextxy(centerX1 , centerY1 , _T("困难"));
		}
		break;
		case 3:
		{
			settextcolor(RGB(139, 0, 0));//设置字体颜色为粉红色
			outtextxy(centerX1 , centerY1, _T("地狱"));
		}
		break;
		}
		haveground = 1;	// 画完了
	}
	haveground = 1;
}
//point whatblock()
//{
//// 1~7 1 内裤型 2 长条 3 田字型 4 7字型 5反7 6 Z字型 8 反Z
//// 1 内裤型 3 5 4 7
//// 2 长条 1 3 5 7
//// 3 田字型 2 3 4 5
//// 4 7字型 2 3 5 7
//// 5 反7 3 5 7 6
//// 6 Z字型 2 4 5 7
//// 7 反Z 3 5 4 6
//	// 使用当前时间作为随机数种子
//	std::srand(static_cast<unsigned int>(std::time(nullptr)));
//
//	// 生成范围在 1 到 70 之间的随机数
//		int Num = std::rand() % 70 + 1;
//		point p[4];
//		if (Num >= 1 && Num <= 10) {
//			p[0].x = 2;
//			p[0].y = 2;
//		}
//
//}
void rotate(block* nblock) // 旋转
{
	btemp = *nblock;
	// 保存原始状态
	point original[4];
	for (int i = 0; i < 4; i++) {
		original[i] = nblock->smblock[i];
	}

	// 选取中心点（这里选择第二个方块作为中心点）
	point center = nblock->smblock[1];

	// 使用旋转矩阵进行旋转
	for (int i = 0; i < 4; i++) {
		int dx = nblock->smblock[i].x - center.x;
		int dy = nblock->smblock[i].y - center.y;
		nblock->smblock[i].x = center.x - dy;
		nblock->smblock[i].y = center.y + dx;
	}

	// 检查旋转后是否碰撞或越界
	if (iscrash(*nblock)) {
		// 恢复到原始状态
		for (int i = 0; i < 4; i++) {
			nblock->smblock[i] = original[i];
		}
	}
}
void drop(block* nblock) // 下落
{
	for (int i = 0; i < 4; i++) {
		nblock->smblock[i].y++;
	}
}
void drawline() {
	for (int i = 0; i < 19; i++) {
		for (int j = 0;j < 12; j++) {
			if (gameMap[i][j] == true) { //灰色格子
				setlinecolor(BLACK);//设置线条颜色为黑色
				setlinestyle(PS_SOLID, 2);
				setfillcolor(RGB(128, 128, 128));//设置填充颜色为灰色
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
	setlinecolor(RGB(128, 128, 128));//设置线条颜色为灰色
	setlinestyle(PS_SOLID, 3);//设置线条粗细为5
	setfillcolor(WHITE);//设置填充颜色为白色
	fillrectangle(60, 70, 240, 160);
	settextcolor(RGB(255, 0, 0));//设置字体颜色为红色
	settextstyle(40, 0, _T("黑体"));//设置字体大小为30，字体为黑体
	int centerX3 = (180 - textwidth(_T("再来一局"))) / 2;
	int centerY3 = (130 - textheight(_T("再来一局"))) / 2;
	outtextxy(60 + centerX3, 50 + centerY3, _T("再来一局"));//输出文字
	// 返回主菜单
	setlinecolor(RGB(128, 128, 128));//设置线条颜色为灰色
	setlinestyle(PS_SOLID, 3);//设置线条粗细为5
	setfillcolor(WHITE);//设置填充颜色为白色
	fillrectangle(360, 70, 540, 160);
	settextcolor(RGB(255, 0, 0));//设置字体颜色为红色
	settextstyle(50, 0, _T("黑体"));//设置字体大小为30，字体为黑体
	int centerX4 = (180 - textwidth(_T("主菜单"))) / 2;
	int centerY4 = (130 - textheight(_T("主菜单"))) / 2;
	outtextxy(360 + centerX4, 50 + centerY4, _T("主菜单"));//输出文字
	while (1) {
		peekmessage(&msg, EX_MOUSE);// 获取鼠标消息
		if (isinarea(msg.x, msg.y, 360, 70, 540, 160)) {
			drawmsg_to_select(360, 70, 540, 160, 8, 20, 5);
			yes = 1;
		}
		else if(isinarea(msg.x, msg.y, 60, 70, 240, 160))
		{
			drawmsg_to_select(60, 70, 240, 160, 8, 20, 5);
			yes = 1;
		}
		else if (!isinarea(msg.x, msg.y, 60, 70, 240, 160)||!isinarea(msg.x, msg.y, 360, 70, 540, 160))
		{
			if (yes == 1) {
				undo_drawmsg_to_select(60, 70, 240, 160, 8, 20, 5);
				undo_drawmsg_to_select(360, 70, 540, 160, 8, 20, 5);
				yes = 0;
			}
		}
		if (msg.message == WM_LBUTTONUP && isinarea(msg.x, msg.y, 60, 70, 240, 160)) {
			return 1;
		}
		else if (msg.message == WM_LBUTTONUP && isinarea(msg.x, msg.y, 360, 70, 540, 160)) {
			return 0;
		}
	}
}
void overselect()
{
	msg = { 0 };
	initgraph(600, 400, EX_NOCLOSE | EX_SHOWCONSOLE | EX_NOMINIMIZE | EX_DBLCLKS);//初始化窗口
	setbkcolor(WHITE);//设置背景颜色为白色
	cleardevice(); 
	drawallframe(600, 400);
	settextcolor(RGB(255, 0, 0));//设置字体颜色为红色
	settextstyle(60, 0, _T("黑体"));//设置字体大小为30，字体为黑体
	int centerX4 = (600 - textwidth(_T("游 | 戏 | 结 | 束"))) / 2;
	int centerY4 = (400 - textheight(_T("游 | 戏 | 结 | 束"))) / 2;
	outtextxy(0 + centerX4, 100 + centerY4, _T("游 | 戏 | 结 | 束"));//输出文字
	recordscore();
	if (overmousemsg()) {
		closegraph();
		std::cout << "再来一局" << std::endl;
		gameplay();
	}
	else {
		std::cout << "主 菜 单" << std::endl;
		to_select();
	}
}	
void keymsg(block *now)
{
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		std::cout << "上箭头键被按下" << std::endl;
		rotate(now);
		isrotate = 1;
	}
	// 检测下箭头键
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		std::cout << "下箭头键被按下" << std::endl;
		vy++;
	}
	// 检测左箭头键
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		std::cout << "左箭头键被按下" << std::endl;
		vx--;
	}
	// 检测右箭头键
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		std::cout << "右箭头键被按下" << std::endl;
		vx++;
	}
	if (GetKeyState(VK_ESCAPE) & 0x8000 && GetKeyState(VK_SPACE) & 0x8000) {
		std::cout << "游戏暂停" << std::endl;
		stop1 = 1;
		haveground = 0;
	}

}
void solvekeymsg(block* now,block next) {
	if (stop1) {
		setbkmode(TRANSPARENT);
		settextcolor(RGB(0, 0, 255));//设置字体颜色为粉红色
		settextstyle(70, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		outtextxy(100, 160, _T("暂 停"));
		outtextxy(100, 250, _T("按 BACK 继续"));
		outtextxy(60, 340, _T("按 ESC 主菜单"));
		Sleep(1000);
		while (1) {
			stop1 = 0;
			if (GetAsyncKeyState(VK_BACK) & 0x8000 ){
				std::cout << "游戏继续" << std::endl;
				drawgameframe(next);
				break;
			}
			else if (GetKeyState(VK_ESCAPE) & 0x8000)
			{
				std::cout << "返回主菜单" << std::endl;
				to_select();
			}
			Sleep(20);
		}
		drawgameframe(next); 
		drawblock(*now);
		settextcolor(RGB(0, 0, 255));//设置字体颜色为粉红色
		settextstyle(80, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		outtextxy(80, 160, _T(" 三 ！"));
		haveground = 0;
		Sleep(1000);
		drawgameframe(next);
		drawblock(*now);
		settextcolor(RGB(0, 0, 255));//设置字体颜色为粉红色
		settextstyle(80, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		outtextxy(80, 160, _T(" 二 ！"));
		haveground = 0;
		Sleep(1000);
		drawgameframe(next);
		drawblock(*now);
		settextcolor(RGB(0, 0, 255));//设置字体颜色为粉红色
		settextstyle(80, 0, _T("黑体"));//设置字体大小为30，字体为黑体
		outtextxy(80, 160, _T(" 一 ！"));
		haveground = 0;
		Sleep(1000);
		drawgameframe(next);
		drawblock(*now);
		setbkmode(OPAQUE);
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
//				std::cout << "消除一行" << std::endl;
//				// 消除该行
//				for (int k = i; k > 0; k--) {
//					for (int j = 0; j < GAME_HEIGHT; j++) {
//						gameMap[k][j] = gameMap[k - 1][j];
//					}
//				}
//				// 最上面一行设为false
//				for (int j = 0; j < GAME_WIDTH; ++j) {
//					gameMap[0][j] = false;
//				}
//			}
//		}
//	}
//	// game.score += fullLines * 100; （假设每消除一行得100分）
//}
void clearFullLines() {
	int fullLines = 0;
	// 遍历每一行
	for (int i = GAME_HEIGHT - 1; i >= 0; --i) {
		bool isFull = true;
		// 检查该行是否为满行
		for (int j = 0; j < GAME_WIDTH; ++j) {
			if (!gameMap[i][j]) {
				isFull = false;
				break;
			}
		}
		if (isFull) {
			++fullLines;
			std::cout << "消除一行" << std::endl;
			// 消除该行，将上方行依次下移
			for (int k = i; k > 0; k--) {
				for (int j = 0; j < GAME_WIDTH; j++) {
					gameMap[k][j] = gameMap[k - 1][j];
				}
			}
			// 最上面一行设为 false
			for (int j = 0; j < GAME_WIDTH; ++j) {
				gameMap[0][j] = false;
			}
			// 消除一行后，当前行重新检查，因为上方行下移可能又产生满行
			++i;
		}
	}
	// 每消除一行得 100 分
	game.score += fullLines * 100;
}
void drawnext(block next) // 画下一个
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
	setlinecolor(RGB(r1, g1, b1));//设置边框颜色
	setfillcolor(RGB(r2, g2, b2));//设置填充颜色
	X1 = (200 - ((next.smblock[0].x + next.smblock[3].x) * 30)) / 2 + 320;
	Y1 = (150 - ((next.smblock[0].y + next.smblock[3].y) * 30)) / 2 + 170;
	for (int i = 0; i < 4; i++) {    
		x[i] = next.smblock[i].x * 30 + X1;
		y[i] = next.smblock[i].y * 30 + Y1;
	}
	setlinestyle(PS_SOLID, 1);//设置线条风格为实线
	for (int i = 0; i < 4; i++) {
		fillrectangle(x[i], y[i], x[i] + 30, y[i] + 30);
	}

}
void mousemsg_setting()
{
	int yes11 = 0;
	peekmessage(&msg, EX_MOUSE);// 获取鼠标消息
	while (1)
	{
		peekmessage(&msg, EX_MOUSE);// 获取鼠标消息
		if (isinarea(msg.x, msg.y, 240, 155, 290, 185) && msg.message == WM_LBUTTONDOWN)
		{
			std::cout << "难度发生变化" << std::endl;
			game.difficulty -= 1;
			return;
		}
		else if (isinarea(msg.x, msg.y, 450, 155, 500, 185) && msg.message == WM_LBUTTONDOWN)
		{
			std::cout << "难度发生变化" << std::endl;
			game.difficulty += 1;
			return;
		}
		else if (isinarea(msg.x, msg.y, 340, 500, 460, 540) && msg.message == WM_LBUTTONUP)
		{
			to_select();
		}
		else if (isinarea(msg.x, msg.y, 340, 500, 460, 540))
		{
			if (!yes11)
			{
				drawmsg_to_select(340, 500, 460, 540, 5, 8, 3);
				yes11 = 1;
			}
		}
		else if (!isinarea(msg.x, msg.y, 340, 500, 460, 540))
		{
			undo_drawmsg_to_select(340, 500, 460, 540, 5, 8, 3);
			yes11 = 0;
		}
	}
}
void drawallframe(int x, int y)
{
	setlinestyle(PS_SOLID, 5);//设置线条风格为实线
	setlinecolor(RGB(253, 208, 222));//设置线条颜色为粉红色 但是好浅
	fillrectangle(5, 5, x - 5, y - 5);
	setlinestyle(PS_DASH, 5);//设置线条风格为虚线
	setlinecolor(RGB(71, 166, 74));//设置线条颜色为绿色
	fillrectangle(12, 12, x - 10, y - 10);
	setlinestyle(PS_SOLID, 5);//设置线条风格为实线
	setlinecolor(RGB(253, 208, 222));//设置线条颜色为粉红色 但是好浅
	fillrectangle(19, 19, x - 15 , y - 15);
}
void recordscore()
{
	if (game.score == 0) return;
	if (game.score > readscore()) {
		std::cout << "新纪录" << std::endl;
		std::ofstream outFile("score.txt", std::ios::app);
		if (outFile.is_open()) {
			outFile << game.score << std::endl;
			outFile.close();
		}
		else {
			std::cerr << "无法打开文件" << std::endl;
		} 
	}
	else {
		std::cout << "不是新纪录" << std::endl;
	}
}
int readscore()
{
	std::ifstream inFile("score.txt");
	if (inFile.is_open()) {
		std::string line;
		int lastscore;
		while (std::getline(inFile, line)) {
			lastscore = std::stoi(line);
			std::cout << "读取的分数: " << lastscore << std::endl;
		}
		return lastscore;
		inFile.close();
	}
	else {
		std::cerr << "无法打开文件" << std::endl;
		return 0;
	}
}