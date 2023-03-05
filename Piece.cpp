#include "Piece.h"
#include <iostream>
#include "King.h"

using namespace std;

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

Piece::Piece(Team team, PieceType piecetype, std::pair<int, int> pos)
{
    mType = piecetype;
    mTeam = team;
    mPos = pos;
    desRect.h = 84;
    desRect.w = 84;
    desRect.x = pos.first * WINDOW_WIDTH / 8 + 6;
    desRect.y = pos.second * WINDOW_HEIGHT / 8 + 6;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = 60;
    srcRect.w = 60;
    isDead = false;
}

void Piece::render(SDL_Renderer* renderer){
    mTexture = SDL_CreateTextureFromSurface(renderer, mSurface);
    SDL_RenderCopy(renderer, mTexture, &srcRect, &desRect);
    SDL_DestroyTexture(mTexture);
}

void Piece::PieceMove(std::pair<int, int> pos){
    mPos = pos;
    desRect.x = pos.first * WINDOW_WIDTH / 8 + 6;
    desRect.y = pos.second * WINDOW_HEIGHT / 8 + 6;
}

bool Piece::DeadPiece(){
    return isDead;
}

void Piece::cleanUp(){
    SDL_FreeSurface(mSurface);
}

vector<tuple<int, int, Piece::MoveType>> Piece::pushMove(vector<tuple<int, int, Piece::MoveType>> moveList, tuple<int, int, Piece::MoveType> singleMove, King *king, Piece *field[8][8], bool checkCheck){
    if(!checkCheck)
    {
        moveList.push_back(singleMove);
    }else
    {

    }
    return moveList;
}

King* Piece::getOwnKing(Piece *field[8][8])
{
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

bool Piece::isValidMove(int xStart, int yStart)
{
    for (int i = 0; i < mPossibleMove.size(); i++)
    {

        if (get<0>(mPossibleMove[i]) == xStart && get<1>(mPossibleMove[i]) == yStart)
        {
            mPossibleMove.clear();
            return true;
        }
    }
    return false;
}



