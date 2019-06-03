#include "stdafx.h"

CTetris::CTetris()
{
    sec = 0;
    t1 = t2 = clock();
    prepareGame();
}

void CTetris::initGame()
{
    rot = 0;
    frame = speed;
    curShape  = nextShape;

    nextShape = rand() % 7;
    drawNextBrick(nextShape);

    board.initBrick(curShape);
}

void CTetris::prepareGame()
{
    nextShape = rand() % 7;
    speed = 41;
    numBrick = 0;
    stage = 1;
    draw.drawStage(stage);
    draw.drawTime(sec);
    draw.drawNumBrick(numBrick);
    board.prepareNewgame(curShape);
}

int CTetris::runGame()
{
    int isFinish = 0;

    while(true)
    {
        initGame();
        if(!board.Move(0, 1, curShape)) return 0;
        draw.drawNumBrick(++numBrick);
        while(true)
        {
            if(clock() - t1 >= 1000) drawTime();
            if(--frame == 0)
            {
                frame = speed;
                if(!board.Move(0, 1, curShape)) break;
            }
            isFinish = checkKey();
            if(isFinish == 1) break;
            else if(isFinish < 0) return -1;
            Sleep(20);
        }
        if(checkBrick()) return 1;
    }
}

void CTetris::playGame()
{
    bool Yes;
    int n;

    while(true)
    {
        n = runGame();
        if(n < 0) return;
        else if(n == 1) Yes = draw.gameEndMsg(true);
        else Yes = draw.gameEndMsg(false);

        if(Yes) prepareGame();
        else break;
    }
}

bool CTetris::checkBrick()
{
    board.saveBoard(curShape);
    if(board.checkStage(stage))
    {
        if(++stage < 11)
        {
            board.newStage();
            speed -= 4;
            draw.drawStage(stage);
        }
        else return true;
    }
    return false;
}

int CTetris::checkKey()
{
    int dx, dy, ch;

    if(kbhit())
    {
        dx = dy = 0;
        ch = getch();
        if(ch == 0 || ch == 0xE0)
        {
            ch = getch();
            switch(ch)
            {
                case UP    : board.Rotate(curShape, rot); break;
                case DOWN  : if(!board.Move(dx, ++dy, curShape)) return 1; break;
                case LEFT  : board.Move(--dx, dy, curShape); break;
                case RIGHT : board.Move(++dx, dy, curShape); break;
                default : break;
            }
        }
        else
        {
            switch(ch)
            {
                case ESC : return -1;
                case ' ' : while(board.Move(0, 1, curShape)); return 1;
                case 'p' :
                case 'P' : getch(); break;
                default : break;
            }
        }
    }
    return 0;
}

void CTetris::drawNextBoard()
{
    int i, j;

    for(i = 0; i < BOXSIZE; i++)
    {
        for(j = 0; j < BOXSIZE; j++)
        {
            if(j % (BOXSIZE - 1) == 0 || i % (BOXSIZE - 1) == 0)
                draw.drawBoard(j + Width + 1, i + 16, WALL, 7);
            else draw.drawBoard(j + Width + 1, i + 16, EMPTY, 8);
        }
    }
}

void CTetris::drawNextBrick(int nextShape)
{
    brick.setBrick(nextShape, 0);
    brick.getBrick();
    drawNextBoard();
    brick.drawBrick(Width + 3, 19, BRICK, nextShape);
}

void CTetris::drawTime()
{
    sec = (clock() - t2) / 1000;
    draw.drawTime(sec);
    t1 = clock();
}
