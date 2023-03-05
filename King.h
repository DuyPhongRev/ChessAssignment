#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece
{
    public:
        King(Team team, std::pair<int, int> pos);
        virtual ~King();
        void calcPossibleMoves(Piece* field[8][8], bool checkCheck){};
    protected:

    private:
};

#endif // KING_H
