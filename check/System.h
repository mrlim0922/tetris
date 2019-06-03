#ifndef __TETRIS_H_
#define __TETRIS_H_

#include "stdafx.h"

class CSystem
{
private:
	int curShape;
	int nextShape;
	int rot;
	int speed, frame;
	int stage;
	int numBrick;
	int sec;
	time_t t1, t2;

	CDraw draw;
	CBoard board;
	CBrick brick;

	bool checkBrick();
	void drawTime();
	void drawNextBoard();
	void drawNextBrick(int nextShape);
	int  checkKey();

private:
	int Pulse();
	void PrepareGame();
public:
	void Initialize();
	void Run();
	void Terminate();

public:
	CSystem();
	~CSystem() { ; }
};

#endif

