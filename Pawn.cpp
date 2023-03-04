#include "Pawn.h"

Pawn::Pawn(Team team, std::pair<int, int> pos)
    :Piece(team, PAWN, pos)
{
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/pawn.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/pawn1.png");
    }
}

