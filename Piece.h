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
    enum Team {BLACK, WHITE, NONE};

	enum PieceType {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};

	enum MoveType {NORMAL, CASTLE, ENPASSANT, PROMOTE, CAPTURE, STATIONARY};

	Piece(Team team, PieceType piecetype, pair<int, int> pos);

	void render(SDL_Renderer* renderer);

	void PieceMove(pair<int, int> pos, Piece *field[8][8]);

    bool getDeadPiece();

    void setDeadPiece();

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

    void setOriginPosition();
protected:
    bool isDead;

    Team mTeam;

    PieceType mType;

    MoveType mMove;

    pair<int, int> mPos;

    pair<int, int> originPos;

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
