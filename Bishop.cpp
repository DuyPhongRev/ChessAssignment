#include "Bishop.h"

Bishop::Bishop(Team team, std::pair<int, int> pos)
    :Piece(team, BISHOP, pos)
{
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/bishop.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/bishop1.png");
    }
}

Bishop::~Bishop()
{
    //dtor
}
