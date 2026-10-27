#include <stdio.h>
#include <math.h>
#include <graphics.h>

int flag = 0;
int ChessMap[20][20] = { 0 }; //记录棋子的数组
int MapX = 0, MapY = 0;

int judge(int MapX, int MapY)
{
	int temp = 2 - flag % 2;

	// 横向
	for (int i = MapX - 4, j = MapY; i <= MapX; i++)
	{
		if (i >= 1 && i < 16 && temp == ChessMap[i][j] && temp ==
			ChessMap[i + 1][j] && temp == ChessMap[i + 2][j] &&
			temp == ChessMap[i + 3][j] && temp == ChessMap[i + 4][j])
			return 1;
	}

	// 纵向 
	for (int i = MapX, j = MapY - 4; j <= MapY; j++)
	{
		if (j >= 1 && j < 16 && temp == ChessMap[i][j] && temp ==
			ChessMap[i][j + 1] && temp == ChessMap[i][j + 2] &&
			temp == ChessMap[i][j + 3] && temp == ChessMap[i][j + 4])
			return 1;
	}

	// 左上到右下
	for (int i = MapX - 4, j = MapY - 4; i <= MapX; i++, j++)
	{
		if (i >= 1 && i < 16 && temp == ChessMap[i][j] && temp ==
			ChessMap[i + 1][j + 1] && temp == ChessMap[i + 2][j + 2] &&
			temp == ChessMap[i + 3][j + 3] && temp == ChessMap[i + 4][j + 4])
			return 1;
	}

	// 左下到右上
	for (int i = MapX - 4, j = MapY + 4; i <= MapX; i++, j--)
	{
		if (i >= 1 && i < 16 && temp == ChessMap[i][j] && temp ==
			ChessMap[i + 1][j - 1] && temp == ChessMap[i + 2][j - 2] &&
			temp == ChessMap[i + 3][j - 3] && temp == ChessMap[i + 4][j - 4])
			return 1;
	}

	return 0;
}

int main()
{
	initgraph(600, 500, SHOWCONSOLE);
	IMAGE img;
	loadimage(&img, "五子棋.jpg", 600, 500);
	putimage(0, 0, &img);
	setlinecolor(BLACK);

	int i = 0;
	for (i = 0; i < 20; i++)
	{
		line(0, i * 25, 500, i * 25);
		line(i * 25, 0, i * 25, 500);
	}

	setbkmode(0);
	settextcolor(BLACK);
	outtextxy(515, 60, "玩家1：黑棋");
	outtextxy(515, 100, "玩家2：白棋");

	MOUSEMSG Msg;
	int ChessX = 0;
	int ChessY = 0;

	while (1) {
		Msg = GetMouseMsg(); //  获取鼠标消息

		if (Msg.uMsg == WM_LBUTTONDOWN) { //  鼠标左键按下

			MapX = 0; // 每次点击重置坐标
			MapY = 0;
			bool isClicked = false; // 标记是否点在了交叉点附近

			for (int i = 1; i < 20 && !isClicked; i++) {
				for (int j = 1; j < 20; j++) {
					if (abs(Msg.x - j * 25) < 12 && abs(Msg.y - i * 25) < 12) {
						ChessX = j * 25;
						ChessY = i * 25;
						MapX = i;
						MapY = j;
						isClicked = true;
						break;
					}
				}
			}

			// 如果点在了交叉点，并且这个位置没有棋子
			if (isClicked && ChessMap[MapX][MapY] == 0) {

				// 画棋子
				if (flag % 2 == 0) {
					setfillcolor(BLACK);
					solidcircle(ChessX, ChessY, 10);
					ChessMap[MapX][MapY] = 1;
				}
				else {
					setfillcolor(WHITE);
					solidcircle(ChessX, ChessY, 10);
					ChessMap[MapX][MapY] = 2;
				}

				flag++; // 换人

				// 判赢
				if (judge(MapX, MapY))
				{
					if (1 == flag % 2) {
						MessageBoxW(NULL, L"玩家1：黑棋胜利", L"Game Over", MB_OK);
					}
					else {
						MessageBoxW(NULL, L"玩家2：白棋胜利", L"Game Over", MB_OK);
					}
					break; 
				}
			}
		}
	} 

	(void)getchar();
	return 0;
}