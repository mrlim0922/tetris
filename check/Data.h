#ifndef __DATA_H_
#define __DATA_H_

#include "stdafx.h"

class CData
{
private :

    const char *pStr;

    int  x, y;
    int  score, totalScore;
    int  numLine;
    int  curShape;
    int  curBrick[4][4];
    int  nextBrick[4][4];
    bool isEndStage;

    tag_Board Board[Height][Width];
    CDraw draw;

    int  setY();
    bool crushCheck(int dx, int dy);
    void initBoard();
    void lineCheck();
    void deleteLine(int i);

public :
    CData();
    ~CData() {;}

    void prepareNewgame();
    void drawShadow(int type, int color);
    void getBrick(bool isCurrent);
    void setBrick(int shape);
    void drawBrick(int x, int y, bool isCurrent, int Draw, int color);
    void Rotate(int shape, int &rot);
    void setStartPoint();
    void drawBoard();
    void saveBoard(int color);
    void newStage();
    bool Move(int dx, int dy, int color);
    bool checkStage(int stage);
};
#endif

