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
    //cerr << "check pawn" << endl;
    tmpPosX = xPos;
    tmpPosY = yPos;
    vector<tuple<int, int, Piece::MoveType>> moves;
    if(yPos + dy >= 0 && yPos + dy <= 7 && field[xPos][yPos + dy] == NULL)
    {
        //cerr << "this" << endl;
        if(yPos + dy == 0 || yPos + dy == 7) moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos, yPos + dy, PROMOTE), getOwnKing(field), field);
        else
        {
            //cerr << "here" << endl;
            moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos, yPos + dy, NORMAL), getOwnKing(field), field);
            //cerr << "right here" << endl;
        }
    }
//cerr << "check pawn1" << endl;
    if(mNotMove && field[xPos][yPos + dy * 2] == NULL && field[xPos][yPos + dy] == NULL)
    {
        moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos, yPos + dy * 2, NORMAL), getOwnKing(field), field);
        if(xPos + 1 <= 7 && field[xPos + 1][yPos + dy * 2] != NULL && field[xPos + 1][yPos + dy * 2]->getTeam() != mTeam && field[xPos + 1][yPos + dy * 2]->getType() == PAWN)
        {
            field[xPos + 1][yPos + dy * 2]->setEnpassant();
            mEnpassanted = true;
        }
        if(xPos - 1 >= 0 && field[xPos - 1][yPos + dy * 2] != NULL && field[xPos - 1][yPos + dy * 2]->getTeam() != mTeam && field[xPos - 1][yPos + dy * 2]->getType() == PAWN)
        {
            field[xPos - 1][yPos + dy * 2]->setEnpassant();
            mEnpassanted = true;
        }
    }
//cerr << "check pawn2" << endl;
    if(xPos + dy >= 0 && xPos + dy <= 7 && yPos + dy >= 0 && yPos + dy <= 7 && field[xPos + dy][yPos + dy] != NULL)
    {
        if(field[xPos + dy][yPos + dy]->getTeam() != mTeam)
        {
            if(yPos + dy == 0 || yPos + dy == 7) moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dy, yPos + dy, PROMOTE), getOwnKing(field), field);
            else moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + dy, yPos + dy, CAPTURE), getOwnKing(field), field);
        }
    }
//cerr << "check pawn3" << endl;
    if(xPos - dy <= 7 && xPos - dy >= 0 && yPos + dy >= 0 && yPos + dy <= 7 && field[xPos - dy][yPos + dy] != NULL)
    {
        if(field[xPos - dy][yPos + dy]->getTeam() != mTeam)
        {
            if(yPos + dy == 0 || yPos + dy == 7) moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - dy, yPos + dy, PROMOTE), getOwnKing(field), field);
            else moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - dy, yPos + dy, CAPTURE), getOwnKing(field), field);

        }
    }
//cerr << "check pawn4" << endl;
    if(mValidEnpassant)
    {
        if((yPos == 4 || yPos == 5) && xPos + 1 <= 7 && field[xPos + 1][yPos] != NULL && field[xPos + 1][yPos]->getType() == PAWN && field[xPos + 1][yPos]->mEnpassanted)
        {
            moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos + 1, yPos + dy, ENPASSANT), getOwnKing(field), field);
        }
        if((yPos == 4 || yPos == 5) && xPos - 1 >= 0 && field[xPos - 1][yPos] != NULL && field[xPos - 1][yPos]->getType() == PAWN && field[xPos - 1][yPos]->mEnpassanted)
        {
            moves = pushMove(moves, tuple<int, int, Piece::MoveType>(xPos - 1, yPos + dy, ENPASSANT), getOwnKing(field), field);
        }
    }
    mPossibleMove = moves;
}
