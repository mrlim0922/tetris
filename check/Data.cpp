#include "stdafx.h"

const char *brick[] = {
	"0000111100000000001000100010001000000000111100000100010001000100",
	"1000111000000000011001000100000000001110001000000100010011000000",
	"0010111000000000010001000110000000001110100000001100010001000000",
	"0110011000000000011001100000000001100110000000000110011000000000",
	"0110110000000000010001100010000000000110110000001000110001000000",
	"0100111000000000010001100100000000001110010000000100110001000000",
	"1100011000000000001001100100000000001100011000000100110010000000"
};

CData::CData()
{
    //prepareNewgame();
}

void CData::prepareNewgame()
{
    initBoard();
    score = numLine = totalScore = 0;
    draw.drawScore(totalScore);
    draw.drawNumLine(numLine);
}

void CData::initBoard()
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

void CData::drawBoard()
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

void CData::setBrick(int shape)
{
    pStr = brick[shape];
}

void CData::setStartPoint()
{
    x = 4;
    y = -setY();
}

int CData::setY()
{
    int i, j;

    for(i = 3; i >= 0; i--)
    {
        for(j = 0; j < 4; j++)
        {
            if(curBrick[i][j]) return i;
        }
    }
}

void CData::getBrick(bool isCurrent)
{
    int i, j;

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(isCurrent) curBrick[i][j] = *pStr++ - '0';
            else nextBrick[i][j] = *pStr++ - '0';
        }
    }
}

void CData::drawBrick(int x, int y, bool isCurrent, int Draw, int color)
{
    int i, j;
    int (*pBrick)[4];

    pBrick = isCurrent ? curBrick : nextBrick;

    for(i = 3; i >= 0; i--)
    {
        if((y + i) < 1) break;
        for(j = 0; j < 4; j++)
        {
            if(pBrick[i][j]) draw.drawBoard(j + x, i + y, Draw, color);
            else if(!isCurrent) draw.drawBoard(j + x, i + y, EMPTY, 8);
        }
    }
}

bool CData::crushCheck(int dx, int dy)
{
    int i, j;

    for(i = 3; i >= 0; i--)
    {
        if((y + i) < 0) break;
        for(j = 0; j < 4; j++)
        {
            if(curBrick[i][j])
            {
                if(Board[y + dy + i][x + dx + j].type) return true;
            }
        }
    }
    return false;
}

bool CData::Move(int dx, int dy, int color)
{
    if(crushCheck(dx, dy)) return false;

    drawBrick(x, y, true, EMPTY, 8);
    drawShadow(EMPTY, 8);
    x += dx;
    y += dy;
    drawShadow(SHADOW, 7);
    drawBrick(x, y, true, BRICK, color);

    return true;
}

void CData::drawShadow(int type, int color)
{
    int dy = 0;

    while(!crushCheck(0, ++dy));
    drawBrick(x, y + dy - 1, true, type, color);
}

void CData::Rotate(int shape, int &rot)
{
    const char *tmp;
    tmp = pStr - 16;

    if(rot == 3)setBrick(shape);
    getBrick(true);
    pStr = tmp;

    if(crushCheck(0, 0)) getBrick(true);
    else{
        getBrick(true);

        drawBrick(x, y, true, EMPTY, 8);
        drawShadow(EMPTY, 8);

        if(rot == 3)setBrick(shape);
        getBrick(true);

        drawShadow(SHADOW, 7);
        drawBrick(x, y, true, BRICK, shape);

        rot = ++rot % 4;
    }
}

void CData::saveBoard(int color)
{
    int i, j;

    for(i = 3; i >= 0; i--)
    {
        //if((y + i) < 1) break;
        for(j = 0; j < 4; j++)
        {
            if(curBrick[i][j])
            {
                Board[y + i][x + j].type = BRICK;
                Board[y + i][x + j].color = color;
            }
        }
    }
    lineCheck();
}

void CData::lineCheck()
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

void CData::deleteLine(int i)
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

bool CData::checkStage(int stage)
{
    return score >= (stage + 1) * 100;
}

void CData::newStage()
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
