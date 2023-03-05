#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece
{
    public:
        Bishop(Team team, std::pair<int, int> pos);

        void calcPossibleMoves(Piece* field[8][8], bool checkCheck){};
};

#endif // BISHOP_H
