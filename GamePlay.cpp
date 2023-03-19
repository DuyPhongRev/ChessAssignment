#include "GamePlay.h"

using namespace std;

Piece *pw1 = new Pawn(Pawn::WHITE, pair<int, int>(0,6));
Piece *pw2 = new Pawn(Pawn::WHITE, pair<int, int>(1,6));
Piece *pw3 = new Pawn(Pawn::WHITE, pair<int, int>(2,6));
Piece *pw4 = new Pawn(Pawn::WHITE, pair<int, int>(3,6));
Piece *pw5 = new Pawn(Pawn::WHITE, pair<int, int>(4,6));
Piece *pw6 = new Pawn(Pawn::WHITE, pair<int, int>(5,6));
Piece *pw7 = new Pawn(Pawn::WHITE, pair<int, int>(6,6));
Piece *pw8 = new Pawn(Pawn::WHITE, pair<int, int>(7,6));

Rook *rw1 = new Rook(Rook::WHITE, pair<int, int>(0,7));
Rook *rw2 = new Rook(Rook::WHITE, pair<int, int>(7,7));
King *kw = new King(King::WHITE, pair<int, int>(4,7));
Queen *qw = new Queen(Queen::WHITE, pair<int, int>(3,7));
Knight *kw1 = new Knight(Knight::WHITE, pair<int, int>(1,7));
Knight *kw2 = new Knight(Knight::WHITE, pair<int, int>(6,7));
Bishop *bw1 = new Bishop(Bishop::WHITE, pair<int, int>(2,7));
Bishop *bw2 = new Bishop(Bishop::WHITE, pair<int, int>(5,7));

Piece *pb1 = new Pawn(Pawn::BLACK, pair<int, int>(0,1));
Piece *pb2 = new Pawn(Pawn::BLACK, pair<int, int>(1,1));
Piece *pb3 = new Pawn(Pawn::BLACK, pair<int, int>(2,1));
Piece *pb4 = new Pawn(Pawn::BLACK, pair<int, int>(3,1));
Piece *pb5 = new Pawn(Pawn::BLACK, pair<int, int>(4,1));
Piece *pb6 = new Pawn(Pawn::BLACK, pair<int, int>(5,1));
Piece *pb7 = new Pawn(Pawn::BLACK, pair<int, int>(6,1));
Piece *pb8 = new Pawn(Pawn::BLACK, pair<int, int>(7,1));

Rook *rb1 = new Rook(Rook::BLACK, pair<int, int>(0,0));
Rook *rb2 = new Rook(Rook::BLACK, pair<int, int>(7,0));
King *kb = new King(King::BLACK, pair<int, int>(4,0));
Queen *qb = new Queen(Queen::BLACK, pair<int, int>(3,0));
Knight *kb1 = new Knight(Knight::BLACK, pair<int, int>(1,0));
Knight *kb2 = new Knight(Knight::BLACK, pair<int, int>(6,0));
Bishop *bb1 = new Bishop(Bishop::BLACK, pair<int, int>(2,0));
Bishop *bb2 = new Bishop(Bishop::BLACK, pair<int, int>(5,0));

GamePlay::GamePlay(){
isRunning = true;
xStart = -1;
yStart = -1;
xEnd = -1;
yEnd = -1;
}

GamePlay::~GamePlay(){
    //dtor
}

bool GamePlay::initWindow(){
    WINDOW_HEIGHT = 800;
    WINDOW_WIDTH = 800;
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
    sMove = Mix_LoadWAV("sound/Move.mp3");
    sCapture = Mix_LoadWAV("sound/Capture.mp3");
    sNotify = Mix_LoadWAV("sound/Notify.mp3");
    sStartGame = Mix_LoadWAV("sound/StartGame.mp3");
    sCastle = Mix_LoadWAV("sound/Castle.mp3");
    sCheck = Mix_LoadWAV("sound/Check.mp3");
    gameStart = true;
    currentMove = Piece::NONE;
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
        isRunning = false;
    }
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_GetMouseState(&xStart, &yStart);
            xStart /= 100;
            yStart /= 100;
            if (field[xStart][yStart] != NULL && field[xStart][yStart]->getTeam() == MoveTurn)
            {
                clickedOn = field[xStart][yStart];
                if(MoveTurn == Piece::WHITE) field[xStart][yStart]->calcPossibleMoves(field);
                else field[xStart][yStart]->calcPossibleMoves(field);
            }
        }
        else if(event.type == SDL_MOUSEBUTTONUP && field[xStart][yStart] != NULL && field[xStart][yStart]->getTeam() == MoveTurn)
        {
            SDL_GetMouseState(&xEnd, &yEnd);
            xEnd /= 100;
            yEnd /= 100;
            if(field[xStart][yStart]->isValidMove( xEnd, yEnd))
            {
                if(xStart != xEnd || yStart != yEnd)
                {
                    if(field[xEnd][yEnd] != NULL) Capture = true;
                    Movement = true;
                    clickedOn = NULL;
                }
                currentMove = field[xStart][yStart]->PieceMove(pair<int, int>(xEnd, yEnd), field);
            }else clickedOn = NULL;
            if(currentMove == Piece::PROMOTE)
            {
                tryToPromote();
            }
        }
}

void GamePlay::tryToPromote(){
    while(true)
    {
        SDL_WaitEvent(&event);
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                    field[xEnd][yEnd] = new Rook(field[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    break;
                case SDLK_DOWN:
                    field[xEnd][yEnd] = new Knight(field[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    break;
                case SDLK_LEFT:
                    field[xEnd][yEnd] = new Bishop(field[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    break;
                case SDLK_RIGHT:
                    field[xEnd][yEnd] = new Queen(field[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    break;
            }
            Mix_PlayChannel(-1, sMove, 0);
            break;
        }
    }
}

void GamePlay::printCurrentMove(){
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
    Movement = false;
}

bool GamePlay::checkEndGame(){
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if(field[x][y] != NULL)
            {
                if(field[x][y]->getTeam() == MoveTurn)
                {
                    field[x][y]->calcPossibleMoves(field);
                    if(!field[x][y]->getPossibleMove().empty()) return false;
                }
            }
        }
    }
    return true;
}

void GamePlay::sound(){
    if(gameStart)
    {
        Mix_PlayChannel(-1, sStartGame, 0);
        gameStart = false;
    }
    else if(currentMove == Piece::NORMAL)
    {
        kw->setCheck(field, kw->getPossition().first, kw->getPossition().second);
        kb->setCheck(field, kb->getPossition().first, kb->getPossition().second);
        if(kw->getCheck() || kb->getCheck())
        {
            Mix_PlayChannel(-1, sCheck, 0);
            Capture = false;
        }
        else
        {
            if(Capture)
            {
                Mix_PlayChannel(-1, sCapture, 0);
                Capture = false;
            }
            else Mix_PlayChannel(-1, sMove, 0);
        }
        currentMove = Piece::NONE;
    }
    else if(currentMove == Piece::CASTLE)
    {
        Mix_PlayChannel(-1, sCastle, 0);
        currentMove = Piece::NONE;
    }
    else if (currentMove == Piece::ENPASSANT)
    {
        Mix_PlayChannel(-1, sCapture, 0);
        currentMove = Piece::NONE;
    }
    if(checkEndGame())
    {
        SDL_Delay(500);
        Mix_PlayChannel(-1, sNotify, 0);
        SDL_Delay(1000);
    }
}

void GamePlay::update(){
    if(Movement)
    {
        printCurrentMove();
        changeMoveTurn();
    }
    if(checkEndGame())
    {
        isRunning = false;
        if(MoveTurn == Piece::BLACK) cout << "WHITE IS WINNER!" << endl;
        else cout << "BLACK IS WINNER!" << endl;
    }

}

void GamePlay::render(){
    renderBoard();
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(field[x][y] != NULL && !field[x][y]->isDead) field[x][y]->render(renderer);
        }
    }
    SDL_RenderPresent(renderer);
}

bool GamePlay::running(){
    return isRunning;
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
