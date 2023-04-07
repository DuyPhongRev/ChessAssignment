#include "Queen.h"

Queen::Queen(Team team, std::pair<int, int> pos)
    :Piece(team, QUEEN, pos)
{
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/qw.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/qb.png");
    }
}

void Queen::calcPossibleMoves(Piece* field[8][8])
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
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second, CAPTURE), getOwnKing(field), field);
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
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first - dx, mPos.second, CAPTURE), getOwnKing(field), field);
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
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first, mPos.second + dy, CAPTURE), getOwnKing(field), field);
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
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first, mPos.second - dy, CAPTURE), getOwnKing(field), field);
                break;
            }
        }else break;
    }

    ///////////////////////////////////////////////////

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
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dx, CAPTURE), getOwnKing(field), field);
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
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first - dx, mPos.second -dx, CAPTURE), getOwnKing(field), field);
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
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second - dx, CAPTURE), getOwnKing(field), field);
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
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first - dx, mPos.second + dx, CAPTURE), getOwnKing(field), field);
                break;
            }
        }
    }
    mPossibleMove = moves;
}
