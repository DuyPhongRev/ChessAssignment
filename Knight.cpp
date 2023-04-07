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
}

void Knight::calcPossibleMoves(Piece* field[8][8])
{
    vector<tuple<int, int, Piece::MoveType>> moves;
    for(int dx = -2; dx <= 2; dx += 4)
    {
        for (int dy = -1; dy <= 1; dy += 2)
        {
            if(mPos.first + dx <= 7 && mPos.first + dx >= 0 && mPos.second + dy <= 7 && mPos.second + dy >= 0)
            {
                if(field[mPos.first + dx][mPos.second + dy] == NULL)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, NORMAL), getOwnKing(field), field);
                }else if(field[mPos.first + dx][mPos.second + dy]->getTeam() != mTeam)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, CAPTURE), getOwnKing(field), field);
                }
            }
        }
    }

    for(int dy = -2; dy <= 2; dy += 4)
    {
        for (int dx = -1; dx <= 1; dx += 2)
        {
            if(mPos.first + dx <= 7 && mPos.first + dx >= 0 && mPos.second + dy <= 7 && mPos.second + dy >= 0)
            {
                if(field[mPos.first + dx][mPos.second + dy] == NULL)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, NORMAL), getOwnKing(field), field);
                }else if(field[mPos.first + dx][mPos.second + dy]->getTeam() != mTeam)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, CAPTURE), getOwnKing(field), field);
                }
            }
        }
    }
    mPossibleMove = moves;
}
