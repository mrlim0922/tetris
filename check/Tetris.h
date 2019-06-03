#ifndef __TETRIS_H_
#define __TETRIS_H_

#include "Board.h"
#include "Brick.h"

class CTetris
{
private :
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
    void initGame();
    void prepareGame();
    void drawTime();
    void drawNextBoard();
    void drawNextBrick(int nextShape);
    int  checkKey();
    int  runGame();

public :
    CTetris();
    ~CTetris() {;}

    void playGame();
};

#endif


