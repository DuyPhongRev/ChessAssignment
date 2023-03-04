#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece
{
    public:
        Bishop(Team team, std::pair<int, int> pos);
        virtual ~Bishop();

    protected:

    private:
};

#endif // BISHOP_H
