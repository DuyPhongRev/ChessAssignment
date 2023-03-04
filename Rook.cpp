#include "Rook.h"

Rook::Rook(Team team, std::pair<int, int> pos)
    :Piece(team, ROOK, pos)
{
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/rook.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/rook1.png");
    }
}

Rook::~Rook()
{
    //dtor
}
