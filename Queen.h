#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Piece
{
    public:
        Queen(Team team, std::pair<int, int> pos);

        void calcPossibleMoves(Piece* field[8][8], bool checkCheck);

};

#endif // QUEEN_H
