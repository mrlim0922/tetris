#ifndef __BRICK_H_
#define __BRICK_H_

#include "stdafx.h"

class CBrick
{
private:

	const char *pStr;
	int  curBrick[4][4];

	CDraw draw;

public:
	CBrick();
	~CBrick() { ; }

	void setBrick(int shape, int rot);
	void getBrick();
	void drawBrick(int x, int y, int type, int color);
	bool checkBrick(int i, int j) { return curBrick[i][j]; }
	int  getY();
};

#endif


