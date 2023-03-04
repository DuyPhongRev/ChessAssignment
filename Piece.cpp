#include "Piece.h"
#include <iostream>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

Piece::Piece(Team team, PieceType piecetype, std::pair<int, int> pos)
{
    mPos = pos;
    desRect.h = 84;
    desRect.w = 84;
    desRect.x = pos.first * WINDOW_WIDTH / 8 + 8;
    desRect.y = pos.second * WINDOW_HEIGHT / 8 + 6;
    srcRect = {0, 0, 60, 60};
}

void Piece::render(SDL_Renderer* renderer){
    mTexture = SDL_CreateTextureFromSurface(renderer, mSurface);
    if (mTexture == NULL) std::cout << 1;
    SDL_RenderCopy(renderer, mTexture, &srcRect, &desRect);
}

void Piece::PieceMove(std::pair<int, int> pos){
    desRect.x = pos.first * WINDOW_WIDTH / 8 + 8;
    desRect.y = pos.second * WINDOW_HEIGHT / 8 + 6;
}











