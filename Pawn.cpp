#include "Pawn.h"
#include <iostream>

Pawn::Pawn(Team team, std::pair<int, int> pos)
    :Piece(team, PAWN, pos)
{
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/pw.png");
        dy = - 1;
    }else
    {
        Piece::mSurface = IMG_Load("src/pb.png");
        dy = + 1;
    }
}

void Pawn::calcPossibleMoves(Piece* field[8][8], int xPos = 0, int yPos = 0)
{
    tmpPosX = xPos;
    tmpPosY = yPos;
    vector<tuple<int, int, Piece::MoveType>> moves;
    if(yPos + dy >= 0 && yPos + dy <= 7 && field[xPos][yPos + dy] == NULL)
    {
        if(yPos + dy == 0 || yPos + dy == 7) moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos, yPos + dy, PROMOTE), getOwnKing(field), field);
        else
        {
            moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos, yPos + dy, NORMAL), getOwnKing(field), field);
        }
    }
    if(mNotMove && field[xPos][yPos + dy * 2] == NULL && field[xPos][yPos + dy] == NULL)
    {
        moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos, yPos + dy * 2, NORMAL), getOwnKing(field), field);
        if(xPos + 1 <= 7 && field[xPos + 1][yPos + dy * 2] != NULL && field[xPos + 1][yPos + dy * 2]->getTeam() != mTeam && field[xPos + 1][yPos + dy * 2]->getType() == PAWN)
        {
            field[xPos + 1][yPos + dy * 2]->setEnpassant();
        }
        if(xPos - 1 >= 0 && field[xPos - 1][yPos + dy * 2] != NULL && field[xPos - 1][yPos + dy * 2]->getTeam() != mTeam && field[xPos - 1][yPos + dy * 2]->getType() == PAWN)
        {
            field[xPos - 1][yPos + dy * 2]->setEnpassant();
        }
    }
    if(xPos + dy >= 0 && xPos + dy <= 7 && yPos + dy >= 0 && yPos + dy <= 7 && field[xPos + dy][yPos + dy] != NULL)
    {
        if(field[xPos + dy][yPos + dy]->getTeam() != mTeam)
        {
            if(yPos + dy == 0 || yPos + dy == 7) moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dy, yPos + dy, PROMOTE), getOwnKing(field), field);
            else moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dy, yPos + dy, CAPTURE), getOwnKing(field), field);
        }
    }
    if(xPos - dy <= 7 && xPos - dy >= 0 && yPos + dy >= 0 && yPos + dy <= 7 && field[xPos - dy][yPos + dy] != NULL)
    {
        if(field[xPos - dy][yPos + dy]->getTeam() != mTeam)
        {
            if(yPos + dy == 0 || yPos + dy == 7) moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - dy, yPos + dy, PROMOTE), getOwnKing(field), field);
            else moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - dy, yPos + dy, CAPTURE), getOwnKing(field), field);
        }
    }
    if(mValidEnpassant)
    {
        if(mTeam == WHITE)
        {
            if((yPos == 3) && xPos + 1 <= 7 && field[xPos + 1][yPos] != NULL && field[xPos + 1][yPos]->getType() == PAWN)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + 1, yPos + dy, ENPASSANT), getOwnKing(field), field);
            }
            if((yPos == 3) && xPos - 1 >= 0 && field[xPos - 1][yPos] != NULL && field[xPos - 1][yPos]->getType() == PAWN)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - 1, yPos + dy, ENPASSANT), getOwnKing(field), field);
            }
        }
        else
        {
            if(yPos == 3 && xPos + 1 <= 7 && field[xPos + 1][yPos] != NULL && field[xPos + 1][yPos]->getType() == PAWN)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + 1, yPos + dy, ENPASSANT), getOwnKing(field), field);
            }
            if(yPos == 3 && xPos - 1 >= 0 && field[xPos - 1][yPos] != NULL && field[xPos - 1][yPos]->getType() == PAWN)
            {
                moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - 1, yPos + dy, ENPASSANT), getOwnKing(field), field);
            }
        }
    }
    mPossibleMove = moves;
}
