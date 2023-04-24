#include "Knight.h"
#include <tuple>
#include <iostream>
#include <vector>

Knight::Knight(Team team, std::pair<int, int> pos)
    :Piece(team, KNIGHT, pos)
{
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/kw.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/kb.png");
    }
    originPos.first = pos.first;
    originPos.second = pos.second;
}

void Knight::calcPossibleMoves(Piece* field[8][8], int xPos = 0, int yPos = 0)
{
    tmpPosX = xPos;
    tmpPosY = yPos;
    vector<tuple<int, int, Piece::MoveType>> moves;
    for(int dx = -2; dx <= 2; dx += 4)
    {
        for (int dy = -1; dy <= 1; dy += 2)
        {
            if(xPos + dx <= 7 && xPos + dx >= 0 && yPos + dy <= 7 && yPos + dy >= 0)
            {
                if(field[xPos + dx][yPos + dy] == NULL)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dx, yPos + dy, NORMAL), getOwnKing(field), field);
                }else if(field[xPos + dx][yPos + dy]->getTeam() != mTeam)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dx, yPos + dy, CAPTURE), getOwnKing(field), field);
                }
            }
        }
    }

    for(int dy = -2; dy <= 2; dy += 4)
    {
        for (int dx = -1; dx <= 1; dx += 2)
        {
            if(xPos + dx <= 7 && xPos + dx >= 0 && yPos + dy <= 7 && yPos + dy >= 0)
            {
                if(field[xPos + dx][yPos + dy] == NULL)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dx, yPos + dy, NORMAL), getOwnKing(field), field);
                }else if(field[xPos + dx][yPos + dy]->getTeam() != mTeam)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dx, yPos + dy, CAPTURE), getOwnKing(field), field);
                }
            }
        }
    }
    mPossibleMove = moves;
}
