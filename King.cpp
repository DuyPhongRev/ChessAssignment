#include "King.h"
#include <iostream>
#include "Rook.h"

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

void King::calcPossibleMoves(Piece* field[8][8], int xPos = 0, int yPos = 0)
{
    tmpPosX = xPos;
    tmpPosY = yPos;
    vector<tuple<int, int, Piece::MoveType>> moves;
    for(int dx = -1; dx <= 1; dx ++)
    {
        for (int dy = -1; dy <= 1; dy ++)
        {
            if(xPos + dx <= 7 && xPos + dx >= 0 && yPos + dy >= 0 && yPos + dy <= 7)
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
    if(mNotMove && field[xPos + 1][yPos] == NULL && field[xPos + 2][yPos] == NULL && field[xPos + 3][yPos] != NULL && field[xPos + 3][yPos]->getType() == ROOK && field[xPos + 3][yPos]->getNotMove())
    {
        for(int i = 0; i < (int)moves.size(); i++)
        {
            if(get<0>(moves[i]) == xPos + 1 && get<1>(moves[i]) == yPos)
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + 2, yPos, CASTLE), getOwnKing(field), field);
        }
    }
    if(mNotMove && field[xPos - 1][yPos] == NULL && field[xPos - 2][yPos] == NULL && field[xPos - 3][yPos] == NULL && field[xPos - 4][yPos] != NULL && field[xPos - 4][yPos]->getType() == ROOK && field[xPos -4][yPos]->getNotMove())
    {
        for(int i = 0; i < (int)moves.size(); i++)
        {
            if(get<0>(moves[i]) == xPos - 1 && get<1>(moves[i]) == yPos)
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - 2, yPos, CASTLE), getOwnKing(field), field);
        }
    }
    mPossibleMove = moves;
}

void King::setCheck(Piece *field[8][8], int xKing, int yKing, Team team){
    bool check = false;
    for(int dx = 1; dx < 8; dx++)
    {
        if(dx + xKing <= 7)
        {
            if(field[dx + xKing][yKing] != NULL)
            {
                if(field[dx + xKing][yKing]->getTeam() != mTeam)
                {
                    if(dx == 1 && field[dx + xKing][yKing]->getType() == KING)
                    {
                        check = true;
                    }
                    if(field[dx + xKing][yKing]->getType() == QUEEN || field[dx + xKing][yKing]->getType() == ROOK)
                    {
                        check = true;
                    }else break;
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
                if(field[- dx + xKing][yKing]->getTeam() != mTeam)
                {
                    if(dx == 1 && field[- dx + xKing][yKing]->getType() == KING) check = true;
                    if(field[- dx + xKing][yKing]->getType() == QUEEN || field[- dx + xKing][yKing]->getType() == ROOK)
                    {
                        check = true;
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
                if(field[xKing][dy + yKing]->getTeam() != mTeam)
                {
                    if(dy == 1 && field[xKing][dy + yKing]->getType() == KING) check = true;
                    if(field[xKing][dy + yKing]->getType() == QUEEN || field[xKing][dy + yKing]->getType() == ROOK)
                    {
                        check = true;
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
                if(field[xKing][- dy + yKing]->getTeam() != mTeam)
                {
                    if(dy == 1 && field[xKing][- dy + yKing]->getType() == KING) check = true;
                    if(field[xKing][- dy + yKing]->getType() == QUEEN || field[xKing][- dy + yKing]->getType() == ROOK)
                    {
                        check = true;
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
                if(field[dz + xKing][dz + yKing]->getTeam() != mTeam)
                {
                    if(dz == 1 && field[dz + xKing][dz + yKing]->getType() == KING) check = true;
                    if(field[dz + xKing][dz + yKing]->getType() == QUEEN || field[dz + xKing][dz + yKing]->getType() == BISHOP) check = true;
                    else break;
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
                if(field[-dz + xKing][-dz + yKing]->getTeam() != mTeam)
                {
                    if(dz == 1 && field[-dz + xKing][-dz + yKing]->getType() == KING) check = true;
                    if(field[-dz + xKing][-dz + yKing]->getType() == QUEEN || field[-dz + xKing][-dz + yKing]->getType() == BISHOP) check = true;
                    else break;
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
                if(field[-dz + xKing][dz + yKing]->getTeam() != mTeam)
                {
                    if(dz == 1 && field[-dz + xKing][dz + yKing]->getType() == KING) check = true;
                    if(field[-dz + xKing][dz + yKing]->getType() == QUEEN || field[-dz + xKing][dz + yKing]->getType() == BISHOP) check = true;
                    else break;
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
                if(field[dz + xKing][-dz + yKing]->getTeam() != mTeam)
                {
                    if(dz == 1 && field[dz + xKing][-dz + yKing]->getType() == KING) check = true;
                    if(field[dz + xKing][-dz + yKing]->getType() == QUEEN || field[dz + xKing][-dz + yKing]->getType() == BISHOP) check = true;
                    else break;
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
                    if(field[dx + xKing][dy + yKing]->getTeam() != mTeam)
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
                    if(field[dx + xKing][dy + yKing]->getTeam() != mTeam)
                    {
                        if(field[dx + xKing][dy + yKing]->getType() == KNIGHT) check = true;
                    }
                }
            }
        }
    }
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if(field[x][y] != NULL && field[x][y]->getTeam() != mTeam && field[x][y]->getType() == PAWN)
            {
                if(mTeam == WHITE)
                {
                    if(x + 1 == xKing&& y + 1 == yKing) check = true;
                    else if(x - 1 == xKing&& y + 1 == yKing) check = true;
                }else
                {
                    if(x + 1 == xKing && y - 1 == yKing) check = true;
                    else if(x - 1 == xKing && y - 1 == yKing) check = true;
                }
            }
        }
    }
    mCheck = check;
}

bool King::getCheck(){
    return mCheck;
}
