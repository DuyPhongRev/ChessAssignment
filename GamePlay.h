#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <ctime>
#include <cstdlib>
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

    bool initWindow();

    void renderBoard();

    void renderText(string text, int sizeText, int x, int y);

    void handleEvent();

    void updateConditional();

    void renderAll();

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

    void waitUntilKeyPress();

    void renderPieces();

    void manageAutoBot();

    void holdPiece();

    void movePiece();

    void loadSoundEffect();

    void loadTexture(SDL_Surface *&surface, SDL_Rect *srcRec, SDL_Rect *desRec);

    void menuGame();

    bool quitMenu;

    void renderButton();
private:
    // SDL variable
    SDL_Rect desRect;
    SDL_Texture *boardTexture = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    SDL_Event event;
    SDL_Color textColor = {255, 255, 255, 255};

    // SDL Mixer variable
    Mix_Chunk *sCapture = NULL;
    Mix_Chunk *sMove = NULL;
    Mix_Chunk *sCastle = NULL;
    Mix_Chunk *sCheck = NULL;
    Mix_Chunk *sStartGame = NULL;
    Mix_Chunk *sNotify = NULL;
    Mix_Music *sBackground = NULL;
    TTF_Font *tFont = NULL;
    bool turnOnMusic;

    // Standard variable
    const int WINDOW_HEIGHT = 880;
    const int WINDOW_WIDTH = 880;
    Piece::Team MoveTurn;
    Piece *field[8][8];
    Piece * clickedOn;
    Piece::MoveType currentMove;
    int countMoveToDraw = 0;
    bool Movement;
    bool isRunning;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    bool Capture;
    int mDepth;
    bool isOnePlayer;
    bool selectMode;
    //menu
    SDL_Surface *border = NULL;
    SDL_Surface *menu = NULL;
    SDL_Surface *playButton;
    SDL_Surface *playButtonInside;
    SDL_Surface *musicButton;
    SDL_Surface *musicButtonInside;
    SDL_Surface *exitButton;
    SDL_Surface *exitButtonInside;
    SDL_Surface *musicButtonOff;
    SDL_Surface *musicButtonOffInside;
    SDL_Surface *vsBotButton;
    SDL_Surface *vsBotButtonInside;
    SDL_Surface *vsHumanButton;
    SDL_Surface *vsHumanButtonInside;
    SDL_Surface *backButton;
    SDL_Surface *backButtonInside;
    bool insidePlay;
    bool insideMusic;
    bool insideExit;
    bool insideVsBot;
    bool insideVsHuman;
    bool insideBack;

    // Piece variable
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
