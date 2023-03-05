#include "Knight.h"
#include <tuple>
#include <iostream>
#include <vector>

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
    //std::cout << "prepare" << std::endl;
    for(int dx = -2; dx <= 2; dx += 4)
    {
        for (int dy = -1; dy <= 1; dy += 2)
        {
            if(mPos.first + dx <= 7 && mPos.first + dx >= 0 && mPos.second + dy <= 7 && mPos.second + dy >= 0)
            {
                if(field[mPos.first + dx][mPos.second + dy] == NULL)
                {
                    std::cout << mPos.first + dx << "  " << mPos.second + dy<< std::endl;
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, NORMAL), getOwnKing(field), field, checkCheck);
                }else if(field[mPos.first + dx][mPos.second + dy]->getTeam() != mTeam)
                {
                    std::cout << mPos.first + dx << "  " << mPos.second + dy<< std::endl;
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, NORMAL), getOwnKing(field), field, checkCheck);
                }

            }
        }
    }

    std::cout << "vertical" << std::endl;
    for(int dy = -2; dy <= 2; dy += 4)
    {
        for (int dx = -1; dx <= 1; dx += 2)
        {
            if(mPos.first + dx <= 7 && mPos.first + dx >= 0 && mPos.second + dy <= 7 && mPos.second + dy >= 0)
            {
                if(field[mPos.first + dx][mPos.second + dy] == NULL)
                {
                    std::cout << mPos.first + dx << "  " << mPos.second + dy<< std::endl;
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, NORMAL), getOwnKing(field), field, checkCheck);
                }else if(field[mPos.first + dx][mPos.second + dy]->getTeam() != mTeam)
                {
                    std::cout << mPos.first + dx << "  " << mPos.second + dy<< std::endl;
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, NORMAL), getOwnKing(field), field, checkCheck);
                }
            }
        }
    }
    std::cout << "done" << std::endl;
    mPossibleMove = moves;
}
