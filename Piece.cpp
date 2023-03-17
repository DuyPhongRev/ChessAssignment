#include "Piece.h"
#include <iostream>
#include "King.h"

using namespace std;

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

Piece::Piece(Team team, PieceType piecetype, std::pair<int, int> pos){
    mType = piecetype;
    mTeam = team;
    mPos = pos;
    desRect.h = WINDOW_WIDTH / 8;
    desRect.w = WINDOW_HEIGHT / 8;
    desRect.x = (pos.first ) * WINDOW_WIDTH / 8;
    desRect.y = (pos.second ) * WINDOW_HEIGHT / 8;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = 50;
    srcRect.w = 50;
    isDead = false;
    mNotMove = true;
    mValidEnpassant = false;
    mEnpassanted = false;
    mMove = NORMAL;
}

void Piece::render(SDL_Renderer* renderer){
    mTexture = SDL_CreateTextureFromSurface(renderer, mSurface);
    SDL_RenderCopy(renderer, mTexture, &srcRect, &desRect);
    SDL_DestroyTexture(mTexture);
}

void Piece::PieceMove(pair<int, int> pos, Piece *field[8][8]){
    mPos = pos;
    desRect.x = (pos.first ) * WINDOW_WIDTH / 8;
    desRect.y = (pos.second ) * WINDOW_HEIGHT / 8;
    mNotMove = false;
    if(mMove == CASTLE)
    {
        if(pos.first == 6)
        {
            field[pos.first + 1][pos.second]->PieceMove(pair<int, int>(pos.first - 1,pos.second), field);
            field[pos.first - 1][pos.second] = field[pos.first + 1][pos.second];
            field[pos.first + 1][pos.second] = NULL;
        }
        if(pos.first == 2)
        {
            field[pos.first - 2][pos.second]->PieceMove(pair<int, int>(pos.first + 1,pos.second), field);
            field[pos.first + 1][pos.second] = field[pos.first - 2][pos.second];
            field[pos.first - 2][pos.second] = NULL;
        }
    }
    else if(mMove == ENPASSANT)
    {
            if(mTeam == WHITE && field[pos.first][pos.second + 1] != NULL)
            {
                field[pos.first][pos.second + 1]->isDead = true;
                field[pos.first][pos.second + 1] = NULL;
                mValidEnpassant = false;
            }
            else if(mTeam == BLACK && field[pos.first][pos.second - 1] != NULL)
            {
                field[pos.first][pos.second - 1]->isDead = true;
                field[pos.first][pos.second - 1] = NULL;
                mValidEnpassant = false;
            }
    }
    else if(mMove == PROMOTE)
    {

    }
}

bool Piece::DeadPiece(){
    return isDead;
}

void Piece::cleanUp(){
    SDL_FreeSurface(mSurface);
}

vector<tuple<int, int, Piece::MoveType>> Piece::pushMove(vector<tuple<int, int, Piece::MoveType>> moveList, tuple<int, int, Piece::MoveType> singleMove, King *king, Piece *field[8][8]){
        Piece *tmpField[8][8];
        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
                tmpField[x][y] = field[x][y];
        }
        tmpField[get<0>(singleMove)][get<1>(singleMove)] = tmpField[mPos.first][mPos.second];

        tmpField[mPos.first][mPos.second] = NULL;
        if(king->getPossition().first == mPos.first && king->getPossition().second == mPos.second)
        {
            king->setCheck(tmpField, get<0>(singleMove), get<1>(singleMove));
        }else
        {
            king->setCheck(tmpField, king->getPossition().first, king->getPossition().second);
        }
        if(!king->getCheck())
        {
            moveList.push_back(singleMove);
        }
        king->getCheck();
    return moveList;
}

vector<tuple<int, int, Piece::MoveType>> Piece::getPossibleMove(){
    return mPossibleMove;
}

pair<int, int> Piece::getPossition(){
    return mPos;
}

Piece::MoveType Piece::getMoveType(){
    return mMove;
}

Piece::PieceType Piece::getType(){
    return mType;
}

Piece::Team Piece::getTeam(){
    return mTeam;
}

bool Piece::getNotMove(){
    return mNotMove;
}

void Piece::setEnpassant(){
    mValidEnpassant= true;
}

bool Piece::isEnpassanted(){
    return mEnpassanted;
}

bool Piece::getEnpassant()
{
    return mValidEnpassant;
}

King* Piece::getOwnKing(Piece *field[8][8]){
    for(int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if(field[x][y] != NULL)
            {
                if(field[x][y]->getType() == KING && field[x][y]->getTeam() == mTeam)
                {
                    King *king = static_cast<King*>(field[x][y]);
                    return king;
                }
            }
        }
    }
    return NULL;
}

bool Piece::isValidMove(int xEnd, int yEnd)
{

    for (int i = 0; i < (int)mPossibleMove.size(); i++)
    {

        if (get<0>(mPossibleMove[i]) == xEnd && get<1>(mPossibleMove[i]) == yEnd)
        {
            mMove = get<2>(mPossibleMove[i]);
            return true;
        }
    }
    return false;
}


