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
    originPos.first = pos.first;
    originPos.second = pos.second;
}

void Bishop::calcPossibleMoves(Piece* field[8][8], int xPos = 0, int yPos = 0)
{
    tmpPosX = xPos;
    tmpPosY = yPos;
    vector<tuple<int, int, Piece::MoveType>> moves;
    for (int dx = 1; dx <= 7; dx++)
    {
        if(xPos + dx <= 7 && xPos + dx >= 0 && yPos + dx <= 7 && yPos + dx >= 0)
        {
            if(field[xPos + dx][yPos + dx] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dx, yPos + dx, NORMAL), getOwnKing(field), field);
            }else if(field[xPos + dx][yPos + dx]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dx, yPos + dx, CAPTURE), getOwnKing(field), field);
                break;
            }
        }else break;
    }

    for (int dx = 1; dx <= 7; dx++)
    {
        if(xPos - dx <= 7 && xPos - dx >= 0 && yPos - dx <= 7 && yPos - dx >= 0)
        {
            if(field[xPos - dx][yPos - dx] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - dx, yPos - dx, NORMAL), getOwnKing(field), field);
            }else if(field[xPos - dx][yPos - dx]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - dx, yPos -dx, CAPTURE), getOwnKing(field), field);
                break;
            }
        }
    }

    for (int dx = 1; dx <= 7; dx++)
    {
        if(xPos + dx <= 7 && xPos + dx >= 0 && yPos - dx <= 7 && yPos - dx >= 0)
        {
            if(field[xPos + dx][yPos - dx] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dx, yPos - dx, NORMAL), getOwnKing(field), field);
            }else if(field[xPos + dx][yPos - dx]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dx, yPos - dx, CAPTURE), getOwnKing(field), field);
                break;
            }
        }
    }

    for (int dx = 1; dx <= 7; dx++)
    {
        if(xPos - dx <= 7 && xPos - dx >= 0 && yPos + dx <= 7 && yPos + dx >= 0)
        {
            if(field[xPos - dx][yPos + dx] == NULL)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - dx, yPos + dx, NORMAL), getOwnKing(field), field);
            }else if(field[xPos - dx][yPos + dx] != NULL && field[xPos - dx][yPos + dx]->getTeam() == mTeam)
            {
                break;
            }else
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - dx, yPos + dx, CAPTURE), getOwnKing(field), field);
                break;
            }
        }
    }
    mPossibleMove = moves;
}
