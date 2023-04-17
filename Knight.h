#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"
#include <tuple>

class Knight : public Piece
{
    public:
        Knight(Team team, std::pair<int, int> pos);

        void calcPossibleMoves(Piece* field[8][8], int xPos, int yPos);
};

#endif // KNIGHT_H
