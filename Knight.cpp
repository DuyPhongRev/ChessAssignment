#include "Knight.h"

Knight::Knight(Team team, std::pair<int, int> pos)
    :Piece(team, KNIGHT, pos)
{
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/knight.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/knight1.png");
    }
}

Knight::~Knight()
{
    //dtor
}
