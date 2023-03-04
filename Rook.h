#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece
{
    public:
        Rook(Team team, std::pair<int, int> pos);
        virtual ~Rook();


    private:
};

#endif // ROOK_H
