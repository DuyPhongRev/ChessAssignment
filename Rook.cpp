#include "Rook.h"
#include <iostream>

Rook::Rook(Team team, std::pair<int, int> pos)
    :Piece(team, ROOK, pos)
{
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/rw.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/rb.png");
    }
}

void Rook::calcPossibleMoves(Piece* field[8][8])
{
    vector<tuple<int, int, Piece::MoveType>> moves;
    for (int dx = 1; dx <= 7; dx++)
    {
        if(mPos.first + dx <= 7 && mPos.first + dx >= 0)
        {
            if(field[mPos.first + dx][mPos.second] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second, NORMAL), getOwnKing(field), field);
            }else if(field[mPos.first + dx][mPos.second]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second, NORMAL), getOwnKing(field), field);
                break;
            }
        }else break;
    }

    for (int dx = 1; dx <= 7; dx++)
    {
        if(mPos.first - dx <= 7 && mPos.first - dx >= 0)
        {
            if(field[mPos.first - dx][mPos.second] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first - dx, mPos.second, NORMAL), getOwnKing(field), field);
            }else if(field[mPos.first - dx][mPos.second]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first - dx, mPos.second, NORMAL), getOwnKing(field), field);
                break;
            }
        }else break;
    }

    for (int dy = 1; dy <= 7; dy++)
    {
        if(mPos.second + dy <= 7 && mPos.second + dy >= 0)
        {
            if(field[mPos.first][mPos.second + dy] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first, mPos.second + dy, NORMAL), getOwnKing(field), field);
            }else if(field[mPos.first][mPos.second + dy]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first, mPos.second + dy, NORMAL), getOwnKing(field), field);
                break;
            }
        }else break;
    }

    for (int dy = 1; dy <= 7; dy++)
    {
        if(mPos.second - dy <= 7 && mPos.second - dy >= 0)
        {
            if(field[mPos.first][mPos.second - dy] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first, mPos.second - dy, NORMAL), getOwnKing(field), field);
            }else if(field[mPos.first][mPos.second - dy]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first, mPos.second - dy, NORMAL), getOwnKing(field), field);
                break;
            }
        }else break;
    }
    mPossibleMove = moves;
}
