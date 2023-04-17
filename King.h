#ifndef KING_H
#define KING_H
#include "Piece.h"
#include <utility>
#include<cmath>

class King : public Piece
{
    public:
        King(Team team, std::pair<int, int> pos);

        void calcPossibleMoves(Piece* field[8][8], int xPos, int yPos);

        void setCheck(Piece *field[8][8], int x, int y, Piece::Team team);

        bool getCheck();

    private:
        bool mCheck;
        bool movement;
};

#endif // KING_H
