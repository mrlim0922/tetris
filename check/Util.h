#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#include "stdafx.h"

#define BACK_SPACE       8
#define	ENTER   		13
#define	ESC				27
#define UP				72
#define DOWN			80
#define LEFT			75
#define RIGHT			77
#define PAGE_UP			73
#define PAGE_DOWN		81
#define DEL	    		83

enum { HIDE, SHOW };

enum {
	BLACK,			/*  0 : ��� */
	DARK_BLUE,		/*  1 : ��ο� �Ķ� */
	DARK_GREEN,		/*  2 : ��ο� �ʷ� */
	DARK_SKY_BLUE,	/*  3 : ��ο� �ϴ� */
	DARK_RED,		/*  4 : ��ο� ���� */
	DARK_VIOLET,	/*  5 : ��ο� ���� */
	DARK_YELLOW,	/*  6 : ��ο� ��� */
	GRAY,			/*  7 : ȸ�� */
	DARK_GRAY,		/*  8 : ��ο� ȸ�� */
	BLUE,			/*  9 : �Ķ� */
	GREEN,			/* 10 : �ʷ� */
	SKY_BLUE,		/* 11 : �ϴ� */
	RED,			/* 12 : ���� */
	VIOLET,			/* 13 : ���� */
	YELLOW,			/* 14 : ��� */
	WHITE,			/* 15 : �Ͼ� */
};


void CursorView(char show);
void gotoxy(int x, int y);
void SetColor(int color);

#endif
