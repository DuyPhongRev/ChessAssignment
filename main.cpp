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

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

using namespace std;

bool gRunning = true;

Pawn *pw1 = new Pawn(Pawn::WHITE, std::pair<int, int>(0,6));
Pawn *pw2 = new Pawn(Pawn::WHITE, std::pair<int, int>(1,6));
Pawn *pw3 = new Pawn(Pawn::WHITE, std::pair<int, int>(2,6));
Pawn *pw4 = new Pawn(Pawn::WHITE, std::pair<int, int>(3,6));
Pawn *pw5 = new Pawn(Pawn::WHITE, std::pair<int, int>(4,6));
Pawn *pw6 = new Pawn(Pawn::WHITE, std::pair<int, int>(5,6));
Pawn *pw7 = new Pawn(Pawn::WHITE, std::pair<int, int>(6,6));
Pawn *pw8 = new Pawn(Pawn::WHITE, std::pair<int, int>(7,6));

Rook *rw1 = new Rook(Rook::WHITE, std::pair<int, int>(0,7));
Rook *rw2 = new Rook(Rook::WHITE, std::pair<int, int>(7,7));
King *kw = new King(King::WHITE, std::pair<int, int>(4,7));
Queen *qw = new Queen(Queen::WHITE, std::pair<int, int>(3,7));
Knight *kw1 = new Knight(Knight::WHITE, std::pair<int, int>(1,7));
Knight *kw2 = new Knight(Knight::WHITE, std::pair<int, int>(6,7));
Bishop *bw1 = new Bishop(Bishop::WHITE, std::pair<int, int>(2,7));
Bishop *bw2 = new Bishop(Bishop::WHITE, std::pair<int, int>(5,7));

Pawn *pb1 = new Pawn(Pawn::BLACK, std::pair<int, int>(0,1));
Pawn *pb2 = new Pawn(Pawn::BLACK, std::pair<int, int>(1,1));
Pawn *pb3 = new Pawn(Pawn::BLACK, std::pair<int, int>(2,1));
Pawn *pb4 = new Pawn(Pawn::BLACK, std::pair<int, int>(3,1));
Pawn *pb5 = new Pawn(Pawn::BLACK, std::pair<int, int>(4,1));
Pawn *pb6 = new Pawn(Pawn::BLACK, std::pair<int, int>(5,1));
Pawn *pb7 = new Pawn(Pawn::BLACK, std::pair<int, int>(6,1));
Pawn *pb8 = new Pawn(Pawn::BLACK, std::pair<int, int>(7,1));

Rook *rb1 = new Rook(Rook::BLACK, std::pair<int, int>(0,0));
Rook *rb2 = new Rook(Rook::BLACK, std::pair<int, int>(7,0));
King *kb = new King(King::BLACK, std::pair<int, int>(4,0));
Queen *qb = new Queen(Queen::BLACK, std::pair<int, int>(3,0));
Knight *kb1 = new Knight(Knight::BLACK, std::pair<int, int>(1,0));
Knight *kb2 = new Knight(Knight::BLACK, std::pair<int, int>(6,0));
Bishop *bb1 = new Bishop(Bishop::BLACK, std::pair<int, int>(2,0));
Bishop *bb2 = new Bishop(Bishop::BLACK, std::pair<int, int>(5,0));

int xStart = -1;
int yStart = -1;
int xEnd = -1;
int yEnd = -1;

class GamePlay{
public:

    bool initWindow();

    void renderBoard();

    void handle();

    void update();

    void render();

    bool isRunning();

    void clean();

    void generatePiece();

    void startPos();

    void initMoveTurn();

    void getMoveturn();

    void  changeMoveTurn();
private:
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    SDL_Event event;
    bool Movement;
    Piece::Team MoveTurn;
    Piece *field[8][8];
    Piece * clickedOn;
    Mix_Chunk *sCapture = NULL;
    Mix_Chunk *sMove = NULL;
    Mix_Chunk *sNotify = NULL;
};

bool GamePlay::initWindow(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL INIT FAIL! ERROR LOG: " << SDL_GetError() << endl;
        return false;
    }else
    {
        window = SDL_CreateWindow("CHESS GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
         if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            cout << "MIXER CREATE FAIL! ERROR LOG: " << SDL_GetError() << endl;
            return false;
        }
        if(window == NULL)
        {
            cout << "WINDOW CREATE FAIL! ERROR LOG: " << SDL_GetError() << endl;
            return false;
        }else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL)
            {
                cout << "RENDERER CREATE FAIL! ERROR LOG: " << SDL_GetError() << endl;
                return false;
            }
        }
    }
    sMove = Mix_LoadWAV("sound/move.wav");
    sCapture = Mix_LoadWAV("sound/capture.wav");
    sNotify = Mix_LoadWAV("sound/notify.wav");
    if(sMove == NULL) cout << 1;
    return true;
}

void GamePlay::renderBoard(){
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if((x + y) % 2 == 0)
            {
                if(clickedOn != NULL && clickedOn->isValidMove( x, y)) SDL_SetRenderDrawColor(renderer, 100, 196, 126, 1);
                else SDL_SetRenderDrawColor(renderer, 177, 212, 182, 1);
            }else
            {
                if(clickedOn != NULL && clickedOn->isValidMove( x, y)) SDL_SetRenderDrawColor(renderer, 0, 111, 95, 1);
                else SDL_SetRenderDrawColor(renderer, 74, 118, 103, 1);
            }
            SDL_Rect site;
            site.h = WINDOW_HEIGHT / 8;
            site.w = WINDOW_WIDTH / 8;
            site.x = x * WINDOW_WIDTH / 8;
            site.y = y * WINDOW_HEIGHT / 8;
            SDL_RenderFillRect(renderer, &site);
        }
    }
    kw->setCheck(field, kw->getPossition().first, kw->getPossition().second);
    kb->setCheck(field, kb->getPossition().first, kb->getPossition().second);
    if(kw->getCheck())
    {
        if((kw->getPossition().first + kw->getPossition().second) % 2 == 0)
        {
            SDL_SetRenderDrawColor(renderer, 178, 98, 63, 1);
        }else SDL_SetRenderDrawColor(renderer, 128, 55, 47, 1);
        SDL_Rect site;
        site.h = WINDOW_HEIGHT / 8;
        site.w = WINDOW_WIDTH / 8;
        site.x = kw->getPossition().first * WINDOW_WIDTH / 8;
        site.y = kw->getPossition().second * WINDOW_HEIGHT / 8;
        SDL_RenderFillRect(renderer, &site);
    }
    if(kb->getCheck())
    {
        if((kb->getPossition().first + kb->getPossition().second) % 2 == 0)
        {
            SDL_SetRenderDrawColor(renderer, 178, 98, 63, 1);
        }else SDL_SetRenderDrawColor(renderer, 128, 55, 47, 1);
        SDL_Rect site;
        site.h = WINDOW_HEIGHT / 8;
        site.w = WINDOW_WIDTH / 8;
        site.x = kb->getPossition().first * WINDOW_WIDTH / 8;
        site.y = kb->getPossition().second * WINDOW_HEIGHT / 8;
        SDL_RenderFillRect(renderer, &site);
    }
}

void GamePlay::initMoveTurn(){
    MoveTurn = Piece::WHITE;
}

void  GamePlay::changeMoveTurn(){
    if(MoveTurn == Piece::BLACK) MoveTurn = Piece::WHITE;
    else MoveTurn = Piece::BLACK;
}

void GamePlay::startPos(){
    field[0][1] = pb1;
    field[1][1] = pb2;
    field[2][1] = pb3;
    field[3][1] = pb4;
    field[4][1] = pb5;
    field[5][1] = pb6;
    field[6][1] = pb7;
    field[7][1] = pb8;
    field[0][0] = rb1;
    field[1][0] = kb1;
    field[2][0] = bb1;
    field[3][0] = qb;
    field[4][0] = kb;
    field[5][0] = bb2;
    field[6][0] = kb2;
    field[7][0] = rb2;
    field[0][6] = pw1;
    field[1][6] = pw2;
    field[2][6] = pw3;
    field[3][6] = pw4;
    field[4][6] = pw5;
    field[5][6] = pw6;
    field[6][6] = pw7;
    field[7][6] = pw8;
    field[0][7] = rw1;
    field[1][7] = kw1;
    field[2][7] = bw1;
    field[3][7] = qw;
    field[4][7] = kw;
    field[5][7] = bw2;
    field[6][7] = kw2;
    field[7][7] = rw2;

    for (int y = 2; y < 6; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            field[x][y] = NULL;
        }
    }
}

void GamePlay::handle(){
    SDL_WaitEvent(&event);
    if(event.type == SDL_QUIT)
    {
        gRunning = false;
    }
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_GetMouseState(&xStart, &yStart);
        xStart /= 100;
        yStart /= 100;
        if (field[xStart][yStart] != NULL && field[xStart][yStart]->getTeam() == MoveTurn)
        {
            clickedOn = field[xStart][yStart];
            if(MoveTurn == Piece::WHITE)
            {
                field[xStart][yStart]->calcPossibleMoves(field);
            }
            else
            {
                field[xStart][yStart]->calcPossibleMoves(field);
            }
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP && field[xStart][yStart] != NULL && field[xStart][yStart]->getTeam() == MoveTurn)
    {
        SDL_GetMouseState(&xEnd, &yEnd);
        xEnd /= 100;
        yEnd /= 100;
        if(field[xStart][yStart]->isValidMove( xEnd, yEnd))
        {
            field[xStart][yStart]->PieceMove(std::pair<int, int>(xEnd, yEnd));
            if(field[xEnd][yEnd] != NULL && field[xEnd][yEnd]->getTeam() != field[xStart][yStart]->getTeam())
            {
                Mix_PlayChannel(-1, sCapture, 0);
                field[xEnd][yEnd]->isDead = true;
            }else Mix_PlayChannel(-1, sMove, 0);
            if(xStart != xEnd || yStart != yEnd)
            {
                field[xEnd][yEnd] = field[xStart][yStart];
                field[xStart][yStart] = NULL;
                Movement = true;
                clickedOn = NULL;
            }
        }else
        {
            clickedOn = NULL;
        }
    }
}

void GamePlay::update(){
    if(Movement)
    {
        switch(xEnd)
        {
            case 0:
                cout << " A-" << 8 - yEnd << "   ";
                break;
            case 1:
                cout << " B-" << 8 - yEnd << "   ";
                break;
            case 2:
                cout << " C-" << 8 - yEnd << "   ";
                break;
            case 3:
                cout << " D-" << 8 - yEnd << "   ";
                break;
            case 4:
                cout << " E-" << 8 - yEnd << "   ";
                break;
            case 5:
                cout << " F-" << 8 - yEnd << "   ";
                break;
            case 6:
                cout << " G-" << 8 - yEnd << "   ";
                break;
            case 7:
                cout << " H-" << 8 - yEnd << "   ";
                break;
        }
        if (MoveTurn == Piece::BLACK) cout << endl;
        changeMoveTurn();
        Movement = false;
    }
}

void GamePlay::render(){
    renderBoard();
    if(!pw1->DeadPiece()) pw1->render(renderer);
    if(!pw2->DeadPiece()) pw2->render(renderer);
    if(!pw3->DeadPiece()) pw3->render(renderer);
    if(!pw4->DeadPiece()) pw4->render(renderer);
    if(!pw5->DeadPiece()) pw5->render(renderer);
    if(!pw6->DeadPiece()) pw6->render(renderer);
    if(!pw7->DeadPiece()) pw7->render(renderer);
    if(!pw8->DeadPiece()) pw8->render(renderer);

    if(!rw1->DeadPiece()) rw1->render(renderer);
    if(!rw2->DeadPiece()) rw2->render(renderer);
    if(!kw1->DeadPiece()) kw1->render(renderer);
    if(!kw2->DeadPiece()) kw2->render(renderer);
    if(!bw1->DeadPiece()) bw1->render(renderer);
    if(!bw2->DeadPiece()) bw2->render(renderer);
    if(!kw->DeadPiece()) kw->render(renderer);
    if(!qw->DeadPiece()) qw->render(renderer);

    if(!pb1->DeadPiece()) pb1->render(renderer);
    if(!pb2->DeadPiece()) pb2->render(renderer);
    if(!pb3->DeadPiece()) pb3->render(renderer);
    if(!pb4->DeadPiece()) pb4->render(renderer);
    if(!pb5->DeadPiece()) pb5->render(renderer);
    if(!pb6->DeadPiece()) pb6->render(renderer);
    if(!pb7->DeadPiece()) pb7->render(renderer);
    if(!pb8->DeadPiece()) pb8->render(renderer);

    if(!rb1->DeadPiece()) rb1->render(renderer);
    if(!rb2->DeadPiece()) rb2->render(renderer);
    if(!kb1->DeadPiece()) kb1->render(renderer);
    if(!kb2->DeadPiece()) kb2->render(renderer);
    if(!bb1->DeadPiece()) bb1->render(renderer);
    if(!bb2->DeadPiece()) bb2->render(renderer);
    if(!kb->DeadPiece()) kb->render(renderer);
    if(!qb->DeadPiece()) qb->render(renderer);

    SDL_RenderPresent(renderer);
}

void GamePlay::clean(){
    Mix_FreeChunk(sMove);
    Mix_FreeChunk(sCapture);
    Mix_FreeChunk(sNotify);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    cout << "GAME CLEANED!" << endl;
}

int main(int argc, char* argv[])
{
    GamePlay *chess = new GamePlay;

    if(chess->initWindow())
    {
        chess->startPos();
        chess->initMoveTurn();
        while(gRunning)
        {
            chess->handle();
            chess->update();
            chess->render();
        }
    }
    chess->clean();
    return 0;
}
