#include "Bishop.h"

Bishop::Bishop(Team team, std::pair<int, int> pos)
    :Piece(team, BISHOP, pos)
{
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/bw.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/bb.png");
    }
}

void Bishop::calcPossibleMoves(Piece* field[8][8])
{
    vector<tuple<int, int, Piece::MoveType>> moves;
    for (int dx = 1; dx <= 7; dx++)
    {
        if(mPos.first + dx <= 7 && mPos.first + dx >= 0 && mPos.second + dx <= 7 && mPos.second + dx >= 0)
        {
            if(field[mPos.first + dx][mPos.second + dx] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dx, NORMAL), getOwnKing(field), field);
            }else if(field[mPos.first + dx][mPos.second + dx]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dx, NORMAL), getOwnKing(field), field);
                break;
            }
        }else break;
    }

    for (int dx = 1; dx <= 7; dx++)
    {
        if(mPos.first - dx <= 7 && mPos.first - dx >= 0 && mPos.second - dx <= 7 && mPos.second - dx >= 0)
        {
            if(field[mPos.first - dx][mPos.second - dx] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first - dx, mPos.second - dx, NORMAL), getOwnKing(field), field);
            }else if(field[mPos.first - dx][mPos.second - dx]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first - dx, mPos.second -dx, NORMAL), getOwnKing(field), field);
                break;
            }
        }
    }

    for (int dx = 1; dx <= 7; dx++)
    {
        if(mPos.first + dx <= 7 && mPos.first + dx >= 0 && mPos.second - dx <= 7 && mPos.second - dx >= 0)
        {
            if(field[mPos.first + dx][mPos.second - dx] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second - dx, NORMAL), getOwnKing(field), field);
            }else if(field[mPos.first + dx][mPos.second - dx]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second - dx, NORMAL), getOwnKing(field), field);
                break;
            }
        }
    }

    for (int dx = 1; dx <= 7; dx++)
    {
        if(mPos.first - dx <= 7 && mPos.first - dx >= 0 && mPos.second + dx <= 7 && mPos.second + dx >= 0)
        {
            if(field[mPos.first - dx][mPos.second + dx] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first - dx, mPos.second + dx, NORMAL), getOwnKing(field), field);
            }else if(field[mPos.first - dx][mPos.second + dx] != NULL && field[mPos.first - dx][mPos.second + dx]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first - dx, mPos.second + dx, NORMAL), getOwnKing(field), field);
                break;
            }
        }
    }
    mPossibleMove = moves;
}
