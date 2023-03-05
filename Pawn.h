#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece
{
public:
    Pawn(Team team, std::pair<int, int> pos);
    void calcPossibleMoves(Piece* field[8][8], bool checkCheck);
private:
    int dy;
    int Default;
};

#endif // PAWN_H
