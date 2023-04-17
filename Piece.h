#ifndef PIECE_H
#define PIECE_H
#include "SDL.h"
#include "SDL_image.h"
#include <utility>
#include <vector>
#include <tuple>

using namespace std;

class King;

class Piece
{
public:
    bool isDead;

    bool mEnpassanted;

    enum Team { BLACK, WHITE, NONE};

	enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN, EMPTY };

	enum MoveType { NORMAL, CASTLE, ENPASSANT, PROMOTE, CAPTURE, STATIONARY};

	Piece(Team team, PieceType piecetype, pair<int, int> pos);

	void render(SDL_Renderer* renderer);

	void PieceMove(pair<int, int> pos, Piece *field[8][8]);

    bool DeadPiece();

    void cleanUp();

    Team getTeam();

    PieceType getType();

    MoveType getMoveType();

    pair<int, int> getPossition();

    virtual void calcPossibleMoves(Piece* field[8][8], int xPos, int yPos) = 0;

    vector<tuple<int, int, Piece::MoveType>> pushMove(vector<tuple<int, int, Piece::MoveType>> moveList, tuple<int, int, Piece::MoveType> singleMove, King *king, Piece *tmpField[8][8]);

    bool isValidMove(int x, int y);

    King* getOwnKing(Piece *field[8][8]);

    vector<tuple<int, int, Piece::MoveType>> getPossibleMove();

    bool getNotMove();

    void setEnpassant();

    bool getEnpassant();

    void declineEnpassant(Piece* field[8][8]);

protected:
    Team mTeam;

    PieceType mType;

    MoveType mMove;

    pair<int, int> mPos;

    SDL_Rect srcRect;

    SDL_Rect desRect;

    SDL_Surface *mSurface = NULL;

    SDL_Texture *mTexture = NULL;

    vector<tuple<int, int, Piece::MoveType>> mPossibleMove;

    bool mNotMove;

    bool mValidEnpassant;

    int tmpPosX;

    int tmpPosY;
};

#endif // PIECE_H
