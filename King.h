#ifndef KING_H
#define KING_H
#include "Piece.h"
#include <utility>
#include<cmath>

class King : public Piece
{
    public:
        King(Team team, std::pair<int, int> pos);

        void calcPossibleMoves(Piece* field[8][8], bool checkCheck);

        void setCheck(Piece *field[8][8], int x, int y);

        bool getCheck();

    private:
        bool mCheck;
        bool movement;

};

#endif // KING_H
