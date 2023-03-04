#ifndef PIECE_H
#define PIECE_H
#include "SDL.h"
#include "SDL_image.h"
#include <utility>

class Piece
{
public:
    enum Team { BLACK, WHITE, NONE };

	enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN, EMPTY };

	enum MoveType { NORMAL, CASTLE, ENPASSANT, NEWPIECE, INIT };

	Piece(Team team, PieceType piecetype, std::pair<int, int> pos);

	void render(SDL_Renderer* renderer);

	void PieceMove(std::pair<int, int> pos);

	std::pair<int, int> mPos;
protected:
    SDL_Rect srcRect;
    SDL_Surface *mSurface = NULL;
    SDL_Texture *mTexture = NULL;
    SDL_Rect desRect;
    SDL_Renderer *mRenderer ;
};

#endif // PIECE_H
