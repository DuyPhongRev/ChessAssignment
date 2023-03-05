#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Piece
{
    public:
        Queen(Team team, std::pair<int, int> pos);
        virtual ~Queen();
        void calcPossibleMoves(Piece* field[8][8], bool checkCheck){};
    protected:

    private:
};

#endif // QUEEN_H
