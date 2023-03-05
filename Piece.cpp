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
    desRect.x = pos.first * WINDOW_WIDTH / 8 + 6;
    desRect.y = pos.second * WINDOW_HEIGHT / 8 + 6;
}

bool Piece::DeadPiece(){
    return isDead;
}

void Piece::cleanUp(){
    SDL_FreeSurface(mSurface);
}

void Piece::pushMove(vector<tuple<int, int, Piece::MoveType>> moveList, tuple<int, int, Piece::MoveType> singleMove, King *king, Piece *field[8][8], bool checkCheck){
    if(!checkCheck)
    {
        moveList.push_back(singleMove);
    }else
    {

    }
}






