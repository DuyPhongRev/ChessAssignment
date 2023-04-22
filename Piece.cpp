#include "Piece.h"
#include <iostream>
#include "King.h"

int WINDOW_HEIGHT = 800;
int WINDOW_WIDTH = 800;

using namespace std;

Piece::Piece(Team team, PieceType piecetype, std::pair<int, int> pos){
    mType = piecetype;
    mTeam = team;
    mPos = pos;
    desRect.h = WINDOW_WIDTH / 8;
    desRect.w = WINDOW_HEIGHT / 8;
    desRect.x = pos.first * WINDOW_WIDTH / 8 + 40;
    desRect.y = pos.second  * WINDOW_HEIGHT / 8 + 40;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = 50;
    srcRect.w = 50;
    isDead = false;
    mNotMove = true;
    mValidEnpassant = false;
    mMove = STATIONARY;
    isDead = false;
}

void Piece::render(SDL_Renderer* renderer){
    mTexture = SDL_CreateTextureFromSurface(renderer, mSurface);
    SDL_RenderCopy(renderer, mTexture, &srcRect, &desRect);
    SDL_DestroyTexture(mTexture);
}

void Piece::PieceMove(pair<int, int> pos, Piece *field[8][8]){
    desRect.x = (pos.first ) * WINDOW_WIDTH / 8 + 40;
    desRect.y = (pos.second ) * WINDOW_HEIGHT / 8 + 40;
    if(field[pos.first][pos.second] != NULL && field[pos.first][pos.second]->getTeam() != field[mPos.first][mPos.second]->getTeam())
    {
        field[pos.first][pos.second]->isDead = true;
    }
    if(mPos.first != pos.first || mPos.second != pos.second)
    {
        field[pos.first][pos.second] = field[mPos.first][mPos.second];
        field[mPos.first][mPos.second] = NULL;
    }
    mNotMove = false;
    mPos = pos;
}

void Piece::declineEnpassant(Piece* field[8][8]){
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(field[x][y] != NULL && field[x][y]->getTeam() == mTeam && field[x][y]->getType() == PAWN)
            {
                if(field[x][y]->mValidEnpassant)
                {
                    field[x][y]->mValidEnpassant = false;
                }
            }
        }
    }
}

bool Piece::getDeadPiece(){
    return isDead;
}

void Piece::setDeadPiece(){
    isDead = true;
}

vector<tuple<int, int, Piece::MoveType>> Piece::pushMove(vector<tuple<int, int, Piece::MoveType>> moveList, tuple<int, int, Piece::MoveType> singleMove, King *king, Piece *field[8][8]){
    Piece *tmpField[8][8];
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
            tmpField[x][y] = field[x][y];
    }
    tmpField[get<0>(singleMove)][get<1>(singleMove)] = tmpField[tmpPosX][tmpPosY];

    tmpField[tmpPosX][tmpPosY] = NULL;

    if(king->getPossition().first == tmpPosX && king->getPossition().second == tmpPosY)
    {
        king->setCheck(tmpField, get<0>(singleMove), get<1>(singleMove), king->getTeam());
    }else
    {
        king->setCheck(tmpField, king->getPossition().first, king->getPossition().second, king->getTeam());
    }
    if(!king->getCheck())
    {
        moveList.push_back(singleMove);
    }
    king->setCheck(tmpField, king->getPossition().first, king->getPossition().second, king->getTeam());
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
    mValidEnpassant = true;
}

bool Piece::getEnpassant(){
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

bool Piece::isValidMove(int xEnd, int yEnd){

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
