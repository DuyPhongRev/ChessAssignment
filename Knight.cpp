#include "Knight.h"
#include <tuple>

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

void Knight::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
    vector<tuple<int, int, Piece::MoveType>> moves;

    for(int dx = -2; dx <= 2; dx += 4)
    {
        for (int dy = -1; dy <= 1; dy += 2)
        {
            if(mPos.first + dx <= 7 && mPos.first + dx >= 0 && mPos.second + dy <= 7 && mPos.second + dy >= 0)
            {
                if(field[mPos.first + dx][mPos.second + dy] == NULL)
                {

                }else if(field[mPos.first + dx][mPos.second + dy]->getTeam() != mTeam)
                {

                }
            }
        }
    }

    for(int dy = -2; dy <= 2; dy += 4)
    {
        for (int dx = -1; dx <= 1; dx += 2)
        {
            if(mPos.first + dx <= 7 && mPos.first + dx >= 0 && mPos.second + dy <= 7 && mPos.second + dy >= 0)
            {
                if(field[mPos.first + dx][mPos.second + dy] == NULL)
                {

                }else if(field[mPos.first + dx][mPos.second + dy]->getTeam() != mTeam)
                {

                }
            }
        }
    }
    mPossibleMove = moves;
}
