#include "stdafx.h"

char *brick[] = {
	"0000111100000000001000100010001000000000111100000100010001000100",
	"1000111000000000011001000100000000001110001000000100010011000000",
	"0010111000000000010001000110000000001110100000001100010001000000",
	"0110011000000000011001100000000001100110000000000110011000000000",
	"0110110000000000010001100010000000000110110000001000110001000000",
	"0100111000000000010001100100000000001110010000000100110001000000",
	"1100011000000000001001100100000000001100011000000100110010000000"
};

CBrick::CBrick()
{

}

void CBrick::setBrick(int shape, int rot)
{
    pStr = brick[shape] + rot * 16;
}

void CBrick::getBrick()
{
    int i, j;

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            curBrick[i][j] = *pStr++ - '0';
        }
    }
}

int CBrick::getY()
{
    int i, j;

    for(i = 3; i >= 0; i--)
    {
        for(j = 0; j < 4; j++)
        {
            if(curBrick[i][j]) return -i;
        }
    }
}

void CBrick::drawBrick(int x, int y, int type, int color)
{
    int i, j;

    for(i = 3; i >= 0; i--)
    {
        if((y + i) < 1) break;
        for(j = 0; j < 4; j++)
        {
            if(curBrick[i][j]) draw.drawBoard(j + x, i + y, type, color);
        }
    }
}
