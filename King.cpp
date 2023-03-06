#include "King.h"

using namespace std;

King::King(Team team, std::pair<int, int> pos)
    :Piece(team, KING, pos)
{
    movement = false;
    if(team == WHITE)
    {
        Piece::mSurface = IMG_Load("src/kgw.png");
    }else
    {
        Piece::mSurface = IMG_Load("src/kgb.png");
    }
}

void King::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
    vector<tuple<int, int, Piece::MoveType>> moves;
    for(int dx = -1; dx <= 1; dx ++)
    {
        for (int dy = -1; dy <= 1; dy ++)
        {
            if(mPos.first + dx <= 7 && mPos.first + dx >= 0 && mPos.second + dy >= 0 && mPos.second + dy <= 7)
            {
                if(field[mPos.first + dx][mPos.second + dy] == NULL)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, NORMAL), getOwnKing(field), field, checkCheck);
                }else if(field[mPos.first + dx][mPos.second + dy]->getTeam() != mTeam)
                {
                    moves = pushMove(moves, tuple<int, int, Piece::MoveType>(mPos.first + dx, mPos.second + dy, NORMAL), getOwnKing(field), field, checkCheck);
                }
            }
        }
    }
    mPossibleMove = moves;
}

void King::setCheck(Piece *field[8][8], int xKing, int yKing)
{
    bool check = false;
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if(field[x][y] != NULL && field[x][y]->getTeam() != mTeam)
            {
                if(field[x][y]->getType() == KING)
                {
                    if(abs(field[x][y]->getPossition().first - xKing) <= 1 || abs(field[x][y]->getPossition().second - yKing) <= 1)
                    {
                        check = true;
                    }
                } else if (field[x][y]->getType() == PAWN)
                {
                    if(field[x][y]->getTeam() == BLACK)
                    {
                        if((field[x][y]->getPossition().first + 1 == xKing || field[x][y]->getPossition().first - 1 == xKing) && field[x][y]->getPossition().second + 1 == yKing)
                        {
                            check = true;
                        }
                    }else
                    {
                        if((field[x][y]->getPossition().first + 1 == xKing || field[x][y]->getPossition().first - 1 == xKing) && field[x][y]->getPossition().second - 1 == yKing)
                        {
                            check = true;
                        }
                    }
                }else
                {
                    field[x][y]->calcPossibleMoves(field, false);
                    vector<tuple<int, int, Piece::MoveType>> checkList = field[x][y]->getPossibleMove();
                    for (int i = 0; i < checkList.size(); i++)
                    {
                        if (get<0>(checkList[i]) == xKing && get<1>(checkList[i]) == yKing)
                        {
                            check = true;
                        }
                    }
                }
            }
        }
    }
    mCheck = check;
}

bool King::getCheck()
{
    return mCheck;
}
