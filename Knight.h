#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight : public Piece
{
    public:
        Knight(Team team, std::pair<int, int> pos);
        virtual ~Knight();

    protected:

    private:
};

#endif // KNIGHT_H
