#include "Queen.h"

Queen::Queen(Team team, std::pair<int, int> pos)
    :Piece(team, QUEEN, pos)
{
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/queen.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/queen1.png");
    }
}

Queen::~Queen()
{
    //dtor
}
