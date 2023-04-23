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

    void cleanMenu();

    void setTextColor(int r, int g, int b, int a);
private:
    SDL_Rect desRect;
    SDL_Texture *boardTexture = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    SDL_Event event;
    SDL_Color mTextColor = {255, 255, 255, 255};

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
    Piece *mField[8][8];
    Piece * mClickedOn;
    int mCountMoveToDraw = 0;
    bool mMovement;
    bool mRunning;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    int mDepth;
    bool mIsOnePlayer;
    //menu
    SDL_Surface *border = NULL;
    SDL_Surface *menu = NULL;
    SDL_Surface *playButton= NULL;
    SDL_Surface *playButtonInside= NULL;
    SDL_Surface *musicButton= NULL;
    SDL_Surface *musicButtonInside= NULL;
    SDL_Surface *exitButton= NULL;
    SDL_Surface *exitButtonInside= NULL;
    SDL_Surface *musicButtonOff= NULL;
    SDL_Surface *musicButtonOffInside= NULL;
    SDL_Surface *vsBotButton= NULL;
    SDL_Surface *vsBotButtonInside= NULL;
    SDL_Surface *vsHumanButton= NULL;
    SDL_Surface *vsHumanButtonInside= NULL;
    SDL_Surface *backButton= NULL;
    SDL_Surface *backButtonInside= NULL;
    bool mInsidePlay;
    bool mInsideMusic;
    bool mInsideExit;
    bool mInsideVsBot;
    bool mInsideVsHuman;
    bool mInsideBack;
    bool mSelectMode;

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
