#ifndef __BOARD_H_
#define __BOARD_H_

#include "stdafx.h"

class CBoard
{
private:

	int  x, y;
	int  score, totalScore;
	int  numLine;
	bool isEndStage;

	tag_Board Board[Height][Width];
	CDraw draw;
	CBrick brick;

	void initBoard();
	void lineCheck();
	void deleteLine(int i);
	void shadowBrick(int type, int color);
	void drawShadow(int type, int color);
	bool crushCheck(int dx, int dy);

public:
	CBoard();
	~CBoard() { ; }

	void initBrick(int shape);
	void prepareNewgame(int shape);
	void drawBoard();
	void newStage();
	void saveBoard(int color);
	bool checkStage(int stage);
	bool Move(int dx, int dy, int color);
	void Rotate(int shape, int &rot);
	void setStartPoint() { x = 4; y = brick.getY(); };
};

#endif


