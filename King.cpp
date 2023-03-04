#include "King.h"

King::King(Team team, std::pair<int, int> pos)
    :Piece(team, KING, pos)
{
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/king.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/king1.png");
    }
}

King::~King()
{
    //dtor
}
