#include "stdafx.h"

CBoard::CBoard()
{

}

void CBoard::prepareNewgame(int shape)
{
    initBoard();
    score = numLine = totalScore = 0;
    draw.drawScore(totalScore);
    draw.drawNumLine(numLine);
}

void CBoard::initBrick(int shape)
{
    brick.setBrick(shape, 0);
    brick.getBrick();
    setStartPoint();
}

void CBoard::initBoard()
{
    int i, j;

    for(i = 0; i < Height; i++)
    {
        for(j = 0; j < Width; j++)
        {
            if(j % (Width - 1) == 0 || i % (Height - 1) == 0)
            {
                Board[i][j].type = WALL;
                Board[i][j].color = 7;
            }
            else
            {
                Board[i][j].type = EMPTY;
                Board[i][j].color = 8;
            }
            draw.drawBoard(j, i, Board[i][j].type, Board[i][j].color);
        }
    }
    for(j = 1; j < Width - 1; j++) Board[0][j].type = EMPTY;
}

void CBoard::drawBoard()
{
    int i, j;

    for(i = 1; i < Height - 1; i++)
    {
        for(j = 1; j < Width - 1; j++)
        {
            draw.drawBoard(j, i, Board[i][j].type, Board[i][j].color);
        }
    }
}

bool CBoard::crushCheck(int dx, int dy)
{
    int i, j;

    for(i = 3; i >= 0; i--)
    {
        if((y + dy + i) < 0) break;
        for(j = 0; j < 4; j++)
        {
            if(brick.checkBrick(i, j))
            {
                if(Board[y + dy + i][x + dx + j].type) return true;
            }
        }
    }
    return false;
}

bool CBoard::Move(int dx, int dy, int color)
{
    if(crushCheck(dx, dy)) return false;

    shadowBrick(EMPTY, color);
    x += dx;
    y += dy;
    shadowBrick(BRICK, color);

    return true;
}

void CBoard::drawShadow(int type, int color)
{
    int dy = 0;

    while(!crushCheck(0, ++dy));
    brick.drawBrick(x, y + dy - 1, type == EMPTY ? 0 : SHADOW, color);
}

void CBoard::shadowBrick(int type, int color)
{
    drawShadow(type, type == EMPTY ? 8 : 7);
    brick.drawBrick(x, y, type, color);
}

void CBoard::Rotate(int shape, int &rot)
{
    if(rot == 3) brick.setBrick(shape, 0);
    brick.getBrick();
    brick.setBrick(shape, rot);

    if(crushCheck(0, 0)) brick.getBrick();
    else
	{
        brick.getBrick();
        shadowBrick(EMPTY, shape);

        if(rot == 3)brick.setBrick(shape, 0);
        brick.getBrick();
        shadowBrick(BRICK, shape);

        rot = ++rot % 4;
    }
}

void CBoard::saveBoard(int color)
{
    int i, j;

    for(i = 3; i >= 0; i--)
    {
        if((y + i) < 1) break;
        for(j = 0; j < 4; j++)
        {
            if(brick.checkBrick(i, j))
            {
                Board[y + i][x + j].type = BRICK;
                Board[y + i][x + j].color = color;
            }
        }
    }
    lineCheck();
}

void CBoard::lineCheck()
{
    int  i, j, cnt = 0;

    for(i = Height - 2; i > 0; i--)
    {
        for(j = 1; j < Width - 1; j++)
        {
            if(Board[i][j].type == EMPTY) break;
        }
        if(j == Width - 1)
        {
            deleteLine(i++);
            cnt++;
        }
    }
    if(cnt)
    {
        score += 10 * cnt * cnt;
        totalScore += 10 * cnt * cnt;
        draw.drawScore(totalScore);
    }
}

void CBoard::deleteLine(int i)
{
    int  j;

    for(; i > 1; i--)
    {
        for(j = 1; j < Width - 1; j++)
        {
            Board[i][j] = Board[i - 1][j];
        }
    }
    Sleep(200);
    drawBoard();
    draw.drawNumLine(++numLine);
}

bool CBoard::checkStage(int stage)
{
    return score >= (stage + 1) * 100;
}

void CBoard::newStage()
{
    int i, color = GREEN;

    for(i = 0; i < 3; i++)
    {
        Sleep(500);
        draw.stageEndMsg(color++);
        Sleep(500);
        drawBoard();
    }
    score = 0;
    initBoard();
}
