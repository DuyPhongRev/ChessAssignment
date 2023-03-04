#include "Piece.h"
#include <iostream>

using namespace std;

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

Piece::Piece(Team team, PieceType piecetype, std::pair<int, int> pos)
{
    mType = piecetype;
    desRect.h = 84;
    desRect.w = 84;
    desRect.x = pos.first * WINDOW_WIDTH / 8 + 6;
    desRect.y = pos.second * WINDOW_HEIGHT / 8 + 6;
    srcRect = {0, 0, 60, 60};
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
    cout << Piece::mType << endl;
}

bool Piece::ExitPiece()
{

    return isDead;
}










