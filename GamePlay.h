#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <SDL_mixer.h>

class GamePlay
{
public:
    GamePlay();
    ~GamePlay();
    int WINDOW_HEIGHT;

    int WINDOW_WIDTH;

    bool initWindow();

    void renderBoard();

    void handle();

    void update();

    void render();

    void clean();

    void generatePiece();

    void startPos();

    void initMoveTurn();

    void getMoveturn();

    void  changeMoveTurn();

    void printCurrentMove();

    bool checkEndGame();

    void sound();

    bool gameStart;

    void botPlay();

    bool running();

    void tryToPromote();

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
    bool isRunning;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    bool Capture;
};

#endif // GAMEPLAY_H
