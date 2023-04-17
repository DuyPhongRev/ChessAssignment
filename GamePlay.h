#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

class GamePlay
{
public:
    GamePlay();
    ~GamePlay();
    int WINDOW_HEIGHT;

    int WINDOW_WIDTH;

    bool initWindow();

    void renderBoard();

    void renderText(string text, int x, int y, int sizeText);

    void handle();

    void update();

    void render();

    void clean();

    void generatePiece();

    void startPos();

    void initMoveTurn();

    void getMoveturn();

    void changeMoveTurn();

    void printCurrentMove();

    bool checkEndGame(Piece *tmpPiece[8][8], Piece::Team currentTeam);

    void sound(Piece::MoveType soundType = Piece::STATIONARY);

    bool gameStart;

    void botPlay();

    bool running();

    void specificMove();

    void castle();

    void enpassant();

    void promote();

    int evaluate(Piece *field[8][8]);

    int alphaBetaPrunning(Piece *field[8][8], int depth, int alpha, int beta, bool maximizingPlayer);

private:
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    SDL_Event event;
    bool Movement;
    Piece::Team MoveTurn;
    Piece *field[8][8];
    Piece * clickedOn;
    Piece::MoveType currentMove;
    Mix_Chunk *sCapture = NULL;
    Mix_Chunk *sMove = NULL;
    Mix_Chunk *sCastle = NULL;
    Mix_Chunk *sCheck = NULL;
    Mix_Chunk *sStartGame = NULL;
    Mix_Chunk *sNotify = NULL;
    TTF_Font *tFont = NULL;
    SDL_Color textColor = {61, 65, 81, 0};
    bool isRunning;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    bool Capture;
    int mDepth;
    Piece *pw1 = NULL;
    Piece *pw2 = NULL;
    Piece *pw3 = NULL;
    Piece *pw4 = NULL;
    Piece *pw5 = NULL;
    Piece *pw6 = NULL;
    Piece *pw7 = NULL;
    Piece *pw8 = NULL;
    Rook *rw1 = NULL;
    Rook *rw2 = NULL;
    King *kw = NULL;
    Queen *qw = NULL;
    Knight *kw1 = NULL;
    Knight *kw2 = NULL;
    Bishop *bw1 = NULL;
    Bishop *bw2 = NULL;
    Piece *pb1 = NULL;
    Piece *pb2 = NULL;
    Piece *pb3 = NULL;
    Piece *pb4 = NULL;
    Piece *pb5 = NULL;
    Piece *pb6 = NULL;
    Piece *pb7 = NULL;
    Piece *pb8 = NULL;
    Rook *rb1 = NULL;
    Rook *rb2 = NULL;
    King *kb = NULL;
    Queen *qb = NULL;
    Knight *kb1 = NULL;
    Knight *kb2 = NULL;
    Bishop *bb1 = NULL;
    Bishop *bb2 = NULL;
};

#endif // GAMEPLAY_H
