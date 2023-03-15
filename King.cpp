#include "King.h"
#include <iostream>

using namespace std;

King::King(Team team, std::pair<int, int> pos)
    :Piece(team, KING, pos)
{
    movement = false;
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/kgw.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/kgb.png");
    }
}

void King::calcPossibleMoves(Piece* field[8][8])
{
    vector<tuple<int, int, Piece::MoveType>> moves;
    for(int dx = -1; dx <= 1; dx ++)
    {
        for (int dy = -1; dy <= 1; dy ++)
        {
            if(mPos.first + dx <= 7 && mPos.first + dx >= 0 && mPos.second + dy >= 0 && mPos.second + dy <= 7)
            {
                if(field[mPos.first + dx][mPos.second + dy] == NULL)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, NORMAL), getOwnKing(field), field);
                }else if(field[mPos.first + dx][mPos.second + dy]->getTeam() != mTeam)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, NORMAL), getOwnKing(field), field);
                }
            }
        }
    }
    mPossibleMove = moves;
}

void King::setCheck(Piece *field[8][8], int xKing, int yKing)
{
    bool check = false;

    for(int dx = 1; dx < 8; dx++)
    {
        if(dx + xKing <= 7)
        {
            if(field[dx + xKing][yKing] != NULL)
            {
                if(field[dx + xKing][yKing]->getTeam() != field[xKing][yKing]->getTeam())
                {

                    if(field[dx + xKing][yKing]->getType() == QUEEN || field[dx + xKing][yKing]->getType() == ROOK)
                    {
                        check = true;
                    }else if(field[dx + xKing][yKing]->getType() == KING)
                    {
                        if(dx == 1)
                        {
                            cout << 1 << endl;
                            check = true;
                        }
                        else break;
                    }
                    else break;
                }else
                {
                    break;
                }
            }
        }
    }

    for(int dx = 1; dx < 8; dx++)
    {
        if(- dx + xKing >= 0)
        {
            if(field[- dx + xKing][yKing] != NULL)
            {
                if(field[- dx + xKing][yKing]->getTeam() != field[xKing][yKing]->getTeam())
                {
                    if(field[- dx + xKing][yKing]->getType() == QUEEN || field[- dx + xKing][yKing]->getType() == ROOK)
                    {
                        check = true;
                    }else if(field[-dx + xKing][yKing]->getType() == KING)
                    {
                        if(dx == 1)
                        {
                            cout << 2 << endl;
                            check = true;
                        }
                        else break;
                    }
                    else break;
                }else
                {
                    break;
                }
            }
        }
    }

    for (int dy = 1; dy < 8; dy++)
    {
        if(dy + yKing <= 7)
        {
            if(field[xKing][dy + yKing] != NULL)
            {
                if(field[xKing][dy + yKing]->getTeam() != field[xKing][yKing]->getTeam())
                {
                    if(field[xKing][dy + yKing]->getType() == QUEEN || field[xKing][dy + yKing]->getType() == ROOK)
                    {
                        check = true;
                    }else if(field[xKing][dy + yKing]->getType() == KING)
                    {
                        if(dy == 1)
                        {
                            cout << 3 << endl;
                            check = true;
                        }
                        else break;
                    }
                    else break;

                }else
                {
                    break;
                }
            }
        }
    }

    for (int dy = 1; dy < 8; dy++)
    {
        if(- dy + yKing >= 0)
        {
            if(field[xKing][- dy + yKing] != NULL)
            {
                if(field[xKing][- dy + yKing]->getTeam() != field[xKing][yKing]->getTeam())
                {
                    if(field[xKing][- dy + yKing]->getType() == QUEEN || field[xKing][- dy + yKing]->getType() == ROOK)
                    {
                        check = true;
                    }else if(field[xKing][-dy + yKing]->getType() == KING)
                    {
                        if(dy == 1)
                        {
                            cout << 4 << endl;
                            check = true;
                        }
                        else break;
                    }else break;

                }else
                {
                    break;
                }
            }
        }
    }

    for (int dz = 1; dz < 8; dz++)
    {
        if(dz + xKing <= 7 && dz + yKing <= 7)
        {
            if(field[dz + xKing][dz + yKing] != NULL)
            {
                if(field[dz + xKing][dz + yKing]->getTeam() != field[xKing][yKing]->getTeam())
                {
                    if(field[dz + xKing][dz + yKing]->getType() == QUEEN || field[dz + xKing][dz + yKing]->getType() == BISHOP) check = true;
                    else if(field[dz + xKing][dz + yKing]->getType() == KING || field[dz + xKing][dz + yKing]->getType() == PAWN)
                    {
                        if(dz == 1)
                        {
                            cout << 5 << endl;
                            check = true;
                        }

                        else break;
                    }else break;
                }else
                {
                    break;
                }
            }
        }
    }

    for (int dz = 1; dz < 8; dz++)
    {
        if(-dz + xKing >= 0 && -dz + yKing >= 0)
        {
            if(field[-dz + xKing][-dz + yKing] != NULL)
            {
                if(field[-dz + xKing][-dz + yKing]->getTeam() != field[xKing][yKing]->getTeam())
                {
                    if(field[-dz + xKing][-dz + yKing]->getType() == QUEEN || field[-dz + xKing][-dz + yKing]->getType() == BISHOP) check = true;
                    else if(field[-dz + xKing][-dz + yKing]->getType() == KING || field[-dz + xKing][-dz + yKing]->getType() == PAWN)
                    {
                        if(dz == 1)
                        {
                            cout << 6 << endl;
                            check = true;
                        }
                        else break;
                    }else break;
                }else
                {
                    break;
                }
            }
        }
    }

    for (int dz = 1; dz < 8; dz++)
    {
        if(-dz + xKing >= 0 && dz + yKing <= 7)
        {
            if(field[-dz + xKing][dz + yKing] != NULL)
            {
                if(field[-dz + xKing][dz + yKing]->getTeam() != field[xKing][yKing]->getTeam())
                {
                    if(field[-dz + xKing][dz + yKing]->getType() == QUEEN || field[-dz + xKing][dz + yKing]->getType() == BISHOP) check = true;
                    else if(field[-dz + xKing][dz + yKing]->getType() == KING || field[-dz + xKing][dz + yKing]->getType() == PAWN)
                    {
                        if(dz == 1)
                        {
                            cout << 7 << endl;
                            check = true;
                        }
                        else break;
                    }else break;
                }else
                {
                    break;
                }
            }
        }
    }

    for (int dz = 1; dz < 8; dz++)
    {
        if(dz + xKing <= 7 && -dz + yKing >= 0)
        {
            if(field[dz + xKing][-dz + yKing] != NULL)
            {
                if(field[dz + xKing][-dz + yKing]->getTeam() != field[xKing][yKing]->getTeam())
                {
                    if(field[dz + xKing][-dz + yKing]->getType() == QUEEN || field[dz + xKing][-dz + yKing]->getType() == BISHOP) check = true;
                    else if(field[dz + xKing][-dz + yKing]->getType() == KING || field[dz + xKing][-dz + yKing]->getType() == PAWN)
                    {
                        if(dz == 1)
                        {
                            cout << 8 << endl;
                            check = true;
                        }
                        else break;
                    }else break;
                }else
                {
                    break;
                }
            }
        }
    }

    for(int dx = -2; dx <= 2; dx += 4)
    {
        for (int dy = -1; dy <= 1; dy += 2)
        {
            if(xKing + dx >= 0 && xKing + dx <= 7 && yKing + dy >= 0 && yKing + dy <= 7)
            {
                if(field[dx + xKing][dy + yKing] != NULL)
                {
                    if(field[dx + xKing][dy + yKing]->getTeam() != field[xKing][yKing]->getTeam())
                    {
                        if(field[dx + xKing][dy + yKing]->getType() == KNIGHT) check = true;
                    }
                }
            }
        }
    }

    for(int dy = -2; dy <= 2; dy += 4)
    {
        for (int dx = -1; dx <= 1; dx += 2)
        {
            if(xKing + dx >= 0 && xKing + dx <= 7 && yKing + dy >= 0 && yKing + dy <= 7)
            {
                if(field[dx + xKing][dy + yKing] != NULL)
                {
                    if(field[dx + xKing][dy + yKing]->getTeam() != field[xKing][yKing]->getTeam())
                    {
                        if(field[dx + xKing][dy + yKing]->getType() == KNIGHT) check = true;
                    }
                }
            }
        }
    }

    mCheck = check;
}

bool King::getCheck()
{
    return mCheck;
}
