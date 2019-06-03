#include "stdafx.h"

CDraw::CDraw()
{
    sx = 40 - Width ;
    sy = 0;

    CursorView(HIDE);
    sideMenu();
}

void CDraw::sideMenu()
{
	//int x = MAX_X * 2;
	int x = 4;
	int y = 2;

	SetColor(DARK_YELLOW);
	gotoxy(x, y + 0);	printf("          ");
	gotoxy(x, y + 1);	printf("┃  T E T R I S   ┃");
	gotoxy(x, y + 2);	printf("          ");

	SetColor(YELLOW);
	gotoxy(x + 2, y + 1);	printf("  T E T R I S   ");

	y = 7;
	SetColor(GRAY);
	gotoxy(x + 2, y++);	printf("    Rotation");
	gotoxy(x + 2, y++);	printf("       ↑");
	gotoxy(x + 2, y++);	printf("LEFT ←  → RIGHT");
	gotoxy(x + 2, y++);	printf("       ↓");
	gotoxy(x + 2, y++);	printf("   Fast DOWN");
	y += 3;
	gotoxy(x + 2, y++);	printf("<Esc>   : Game End");
	gotoxy(x + 2, y++);	printf("<SPACE> : Quick Drop");
	gotoxy(x + 2, y++);	printf("<P>     : Pause");
}

void CDraw::drawBoard(int x, int y, int type, int cType)
{
    const int color[] = {SKY_BLUE, BLUE, DARK_YELLOW, YELLOW, GREEN, VIOLET, RED, GRAY, BLACK};
    const char *shape[] = {"  ", "■", "▣", "□"};

    SetColor(color[cType]);
    gotoxy(x * 2 + sx, y + sy);
    printf("%s", shape[type]);
    SetColor(GRAY);
}

void CDraw::drawStage(int stage)
{
	//SetColor(RED);
	gotoxy((Width + 2) * 2 + sx, 2);	printf("S T A G E : %d    ", stage);
}

void CDraw::drawScore(int score)
{
	//SetColor(RED);
	gotoxy((Width + 2) * 2 + sx, 4);	printf("S C O R E : %d    ", score);
}

void CDraw::drawNumLine(int line)
{
	//SetColor(RED);
	gotoxy((Width + 2) * 2 + sx, 6);	printf("L I N E   : %d    ", line);
}

void CDraw::drawNumBrick(int numBrick)
{
	//SetColor(GREEN);
	gotoxy((Width + 2) * 2 + sx, 8);	printf("B R I C K : %d    ", numBrick);
	//SetColor(DARK_GRAY);
}

void CDraw::drawTime(int sec)
{
    int hh, mm;

    hh = sec / 3600;
    mm = (sec % 3600) / 60;
    sec %= 60;

	SetColor(SKY_BLUE);
	gotoxy((Width + 2) * 2 + sx, 10);
	printf("%02d : %02d : %02d", hh, mm, sec);
	SetColor(GRAY);
}

void CDraw::stageEndMsg(int color)
{
    int y = 8;

    SetColor(color);
    gotoxy(3 + sx, y++); puts("                  ");
    gotoxy(3 + sx, y++); puts("    축하 축하     ");
    gotoxy(3 + sx, y++); puts("                  ");
    gotoxy(3 + sx, y++); puts(" Go Go Next Stage ");
    gotoxy(3 + sx, y++); puts("                  ");
    SetColor(GRAY);
}

bool CDraw::gameEndMsg(int Yes)
{
    char ch;
    int  y = 8;

    gotoxy(3 + sx, y++); puts("                  ");
    if(Yes)
    {
        gotoxy(3 + sx, y++); puts(" Clear All Stage! ");
    } else {
        gotoxy(3 + sx, y++); puts("    GAME OVER!    ");
    }
    gotoxy(3 + sx, y++); puts("                  ");
    gotoxy(3 + sx, y++); puts("  One More?  y/n  ");
    gotoxy(3 + sx, y++); puts("                  ");

    while(1)
    {
        ch = getch();
        if(ch == 'y' || ch == 'Y') return true;
        else if(ch == 'n' || ch == 'N') return false;
    }
}


/* ========================================================================== */
/* 화면의 커서를 보이거나 숨기기 */
void CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}

/* ========================================================================== */
/* x, y 좌표로 커서를 움직이는 함수 */
void gotoxy(int x, int y) /*커서이동 함수 부분*/
{
    COORD XY = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}

/* ========================================================================== */
/* 콘솔 색깔을 지정하는 함수 */
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


