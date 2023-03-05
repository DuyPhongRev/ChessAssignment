#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece
{
    public:
        Rook(Team team, std::pair<int, int> pos);

        void calcPossibleMoves(Piece* field[8][8], bool checkCheck);

};

#endif // ROOK_H
