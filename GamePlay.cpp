#include "GamePlay.h"

using namespace std;

GamePlay::GamePlay(){
    mRunning = true;
}

GamePlay::~GamePlay(){
}


//main function of GamePlay
bool GamePlay::initGameData(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cerr << "SDL INIT FAIL! ERROR LOG: " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        window = SDL_CreateWindow("CHESS GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
         if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            cerr << "MIXER CREATE FAIL! ERROR LOG: " << SDL_GetError() << endl;
            return false;
        }
        if (TTF_Init() < 0)
        {
            cerr << "TTF CREATE FAIL! ERROR LOG: " << SDL_GetError() << endl;
            return false;
        }
        if(window == NULL)
        {
            cerr << "WINDOW CREATE FAIL! ERROR LOG: " << SDL_GetError() << endl;
            return false;
        }else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL)
            {
                cerr << "RENDERER CREATE FAIL! ERROR LOG: " << SDL_GetError() << endl;
                return false;
            }
        }
    }
    pw1 = new Pawn(Pawn::WHITE, pair<int, int>(0,6));
    pw2 = new Pawn(Pawn::WHITE, pair<int, int>(1,6));
    pw3 = new Pawn(Pawn::WHITE, pair<int, int>(2,6));
    pw4 = new Pawn(Pawn::WHITE, pair<int, int>(3,6));
    pw5 = new Pawn(Pawn::WHITE, pair<int, int>(4,6));
    pw6 = new Pawn(Pawn::WHITE, pair<int, int>(5,6));
    pw7 = new Pawn(Pawn::WHITE, pair<int, int>(6,6));
    pw8 = new Pawn(Pawn::WHITE, pair<int, int>(7,6));

    rw1 = new Rook(Rook::WHITE, pair<int, int>(0,7));
    rw2 = new Rook(Rook::WHITE, pair<int, int>(7,7));
    kw = new King(King::WHITE, pair<int, int>(4,7));
    qw = new Queen(Queen::WHITE, pair<int, int>(3,7));
    kw1 = new Knight(Knight::WHITE, pair<int, int>(1,7));
    kw2 = new Knight(Knight::WHITE, pair<int, int>(6,7));
    bw1 = new Bishop(Bishop::WHITE, pair<int, int>(2,7));
    bw2 = new Bishop(Bishop::WHITE, pair<int, int>(5,7));

    pb1 = new Pawn(Pawn::BLACK, pair<int, int>(0,1));
    pb2 = new Pawn(Pawn::BLACK, pair<int, int>(1,1));
    pb3 = new Pawn(Pawn::BLACK, pair<int, int>(2,1));
    pb4 = new Pawn(Pawn::BLACK, pair<int, int>(3,1));
    pb5 = new Pawn(Pawn::BLACK, pair<int, int>(4,1));
    pb6 = new Pawn(Pawn::BLACK, pair<int, int>(5,1));
    pb7 = new Pawn(Pawn::BLACK, pair<int, int>(6,1));
    pb8 = new Pawn(Pawn::BLACK, pair<int, int>(7,1));

    rb1 = new Rook(Rook::BLACK, pair<int, int>(0,0));
    rb2 = new Rook(Rook::BLACK, pair<int, int>(7,0));
    kb = new King(King::BLACK, pair<int, int>(4,0));
    qb = new Queen(Queen::BLACK, pair<int, int>(3,0));
    kb1 = new Knight(Knight::BLACK, pair<int, int>(1,0));
    kb2 = new Knight(Knight::BLACK, pair<int, int>(6,0));
    bb1 = new Bishop(Bishop::BLACK, pair<int, int>(2,0));
    bb2 = new Bishop(Bishop::BLACK, pair<int, int>(5,0));

    tFont = TTF_OpenFont("font/Silkscreen-Regular.ttf", 20);

    sMove = Mix_LoadWAV("sound/Move.mp3");
    sCapture = Mix_LoadWAV("sound/Capture.mp3");
    sNotify = Mix_LoadWAV("sound/Notify.mp3");
    sStartGame = Mix_LoadWAV("sound/StartGame.mp3");
    sCastle = Mix_LoadWAV("sound/Castle.mp3");
    sCheck = Mix_LoadWAV("sound/Check.mp3");

    border = IMG_Load("src/border.png");
    menu = IMG_Load("src/menu.png");
    playButton = IMG_Load("src/playbutton.png");
    musicButton = IMG_Load("src/musicbutton.png");
    musicButtonOff = IMG_Load("src/musicbuttonoff.png");
    exitButton = IMG_Load("src/exitbutton.png");
    playButtonInside = IMG_Load("src/playbuttoninside.png");
    musicButtonInside = IMG_Load("src/musicbuttoninside.png");
    exitButtonInside = IMG_Load("src/exitbuttoninside.png");
    musicButtonOffInside = IMG_Load("src/musicbuttonoffinside.png");
    vsBotButton = IMG_Load("src/vsbot.png");
    vsBotButtonInside = IMG_Load("src/vsbotinside.png");
    vsHumanButton = IMG_Load("src/2player.png");
    vsHumanButtonInside = IMG_Load("src/2playerinside.png");
    backButton = IMG_Load("src/backbutton.png");
    backButtonInside = IMG_Load("src/backbuttoninside.png");
    sBackground = Mix_LoadMUS("sound/back.mp3");
    return true;
}


void GamePlay::setNewGame(){
    cerr << "NEW GAME" << endl;
    xStart = -1;
    yStart = -1;
    xEnd = -1;
    yEnd = -1;
    pw1->setOriginPosition();
    pw2->setOriginPosition();
    pw3->setOriginPosition();
    pw4->setOriginPosition();
    pw5->setOriginPosition();
    pw6->setOriginPosition();
    pw7->setOriginPosition();
    pw8->setOriginPosition();

    rw1->setOriginPosition();
    rw2->setOriginPosition();
    kw->setOriginPosition();
    qw->setOriginPosition();
    kw1->setOriginPosition();
    kw2->setOriginPosition();
    bw1->setOriginPosition();
    bw2->setOriginPosition();

    pb1->setOriginPosition();
    pb2->setOriginPosition();
    pb3->setOriginPosition();
    pb4->setOriginPosition();
    pb5->setOriginPosition();
    pb6->setOriginPosition();
    pb7->setOriginPosition();
    pb8->setOriginPosition();

    rb1->setOriginPosition();
    rb2->setOriginPosition();
    kb->setOriginPosition();
    qb->setOriginPosition();
    kb1->setOriginPosition();
    kb2->setOriginPosition();
    bb1->setOriginPosition();
    bb2->setOriginPosition();

    mField[0][1] = pb1;
    mField[1][1] = pb2;
    mField[2][1] = pb3;
    mField[3][1] = pb4;
    mField[4][1] = pb5;
    mField[5][1] = pb6;
    mField[6][1] = pb7;
    mField[7][1] = pb8;
    mField[0][0] = rb1;
    mField[1][0] = kb1;
    mField[2][0] = bb1;
    mField[3][0] = qb;
    mField[4][0] = kb;
    mField[5][0] = bb2;
    mField[6][0] = kb2;
    mField[7][0] = rb2;
    mField[0][6] = pw1;
    mField[1][6] = pw2;
    mField[2][6] = pw3;
    mField[3][6] = pw4;
    mField[4][6] = pw5;
    mField[5][6] = pw6;
    mField[6][6] = pw7;
    mField[7][6] = pw8;
    mField[0][7] = rw1;
    mField[1][7] = kw1;
    mField[2][7] = bw1;
    mField[3][7] = qw;
    mField[4][7] = kw;
    mField[5][7] = bw2;
    mField[6][7] = kw2;
    mField[7][7] = rw2;

    for (int y = 2; y < 6; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            mField[x][y] = NULL;
        }
    }

    MoveTurn = Piece::WHITE;
    mMovement = false;
    quitMenu = false;
    mCountMoveToDraw = 0;
}

void GamePlay::handleEventInGame(){
    if(mIsOnePlayer && MoveTurn == Piece::BLACK)
    {
        manageAutoBot();
    }
    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            quitGame = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            holdPiece();
            break;
        case SDL_MOUSEBUTTONUP:
            if(mClickedOn != NULL && mClickedOn->getTeam() == MoveTurn) movePiece();
            break;
        default:
            break;
    }
}

void GamePlay::soundEffect(Piece::MoveType soundType){
    if(soundType == Piece::CAPTURE)
    {
        Mix_PlayChannel(-1, sCapture, 0);
    }
    else if(soundType == Piece::CASTLE)
    {
        Mix_PlayChannel(-1, sCastle, 0);
    }
    else if(soundType == Piece::NORMAL)
    {
        Mix_PlayChannel(-1, sMove, 0);
    }
    else if(soundType == Piece::PROMOTE)
    {
        Mix_PlayChannel(-1, sCapture, 0);
    }
    if(checkEndGame(mField, MoveTurn))
    {
        Mix_PlayChannel(-1, sNotify, 0);
        SDL_Delay(1000);
    }
}

void GamePlay::updateGameStatus(){
    setTextColor(230,230, 250, 255);
    kb->setCheck(mField, kb->getPossition().first, kb->getPossition().second, Piece::BLACK);
    kw->setCheck(mField, kw->getPossition().first, kw->getPossition().second, Piece::WHITE);
    if(mMovement)
    {
        mCountMoveToDraw++;
        printCurrentMove();
        changeMoveTurn();
    }
    if(checkEndGame(mField, MoveTurn))
    {
        quitGame = true;
        if(kb->getCheck())
        {
            if(mIsOnePlayer) renderText("CONGRASTULATION", 4, -1, -1);
            else renderText("WHITE WIN", 5, -1, -1);
            renderText("-Press any key to exit-", 2, -1, 500);
            waitUntilKeyPress();
        }
        else if(kw->getCheck())
        {
            if(mIsOnePlayer) renderText("LOSE CHICKEN", 5, -1, -1);
            else renderText("BLACK WIN", 5, -1, -1);
            renderText("-Press any key to exit-", 2, -1, 500);
            waitUntilKeyPress();
        }
        else
        {
            renderText("DRAW", 5, -1, -1);
            renderText("-Press any key to exit-", 2, -1, 500);
            waitUntilKeyPress();
        }
        soundEffect();
    }
    if(mCountMoveToDraw == 100)
    {
        quitGame = true;
        renderText("DRAW", 5, -1, -1);
        renderText("-Press any key to exit-", 2, -1, 500);
        waitUntilKeyPress();
        soundEffect();
    }
}

void GamePlay::renderManage(){
    renderChessTable();
    renderPieces();
    SDL_RenderPresent(renderer);
}

void GamePlay::clean(){
    SDL_FreeSurface(border);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(playButton);
    SDL_FreeSurface(playButtonInside);
    SDL_FreeSurface(musicButton);
    SDL_FreeSurface(musicButtonInside);
    SDL_FreeSurface(exitButton);
    SDL_FreeSurface(exitButtonInside);
    SDL_FreeSurface(musicButtonOff);
    SDL_FreeSurface(musicButtonOffInside);
    SDL_FreeSurface(vsBotButton);
    SDL_FreeSurface(vsBotButtonInside);
    SDL_FreeSurface(vsHumanButton);
    SDL_FreeSurface(vsHumanButtonInside);
    SDL_FreeSurface(backButton);
    SDL_FreeSurface(backButtonInside);

    Mix_FreeChunk(sMove);
    Mix_FreeChunk(sCapture);
    Mix_FreeChunk(sNotify);
    Mix_FreeChunk(sCastle);
    Mix_FreeChunk(sCheck);
    Mix_FreeChunk(sStartGame);
    Mix_FreeMusic(sBackground);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    cout << "GAME CLEANED!" << endl;
}


//function of handleEvent
void GamePlay::holdPiece(){
    SDL_GetMouseState(&xStart, &yStart);
    xStart -= 40;
    yStart -= 40;
    xStart /= 100;
    yStart /= 100;
    if (mField[xStart][yStart] != NULL && mField[xStart][yStart]->getTeam() == MoveTurn)
    {
        mClickedOn = mField[xStart][yStart];
        mField[xStart][yStart]->calcPossibleMoves(mField, xStart, yStart);
    }
}

void GamePlay::movePiece(){
    SDL_GetMouseState(&xEnd, &yEnd);
    xEnd -= 40;
    yEnd -= 40;
    xEnd /= 100;
    yEnd /= 100;
    if(mField[xStart][yStart]->isValidMove( xEnd, yEnd))
    {
        mField[xStart][yStart]->PieceMove(pair<int, int>(xEnd, yEnd), mField);
        specificMove();
        if(xStart != xEnd || yStart != yEnd)
        {
            mMovement = true;
            mClickedOn = NULL;
        }
    }else mClickedOn = NULL;
}

void GamePlay::specificMove(){
    if(mClickedOn->getMoveType() == Piece::CASTLE) castle();
    else if(mClickedOn->getMoveType() == Piece::ENPASSANT) enpassant();
    else if(mClickedOn->getMoveType() == Piece::PROMOTE) promote();
    else if(mClickedOn->getMoveType() == Piece::CAPTURE) mCountMoveToDraw = 0;
    if(mClickedOn->getType() == Piece::PAWN) mCountMoveToDraw = 0;
    mClickedOn->declineEnpassant(mField);
    soundEffect(mClickedOn->getMoveType());
}

void GamePlay::castle(){
    if(xEnd == 6)
    {
        mField[xEnd + 1][yEnd]->PieceMove(pair<int, int>(xEnd - 1,yEnd), mField);
    }
    if(xEnd == 2)
    {
        mField[xEnd - 2][yEnd]->PieceMove(pair<int, int>(xEnd + 1,yEnd), mField);
    }
}

void GamePlay::enpassant(){
    if(mClickedOn->getTeam() == Piece::WHITE && mField[xEnd][yEnd + 1] != NULL)
    {
        mField[xEnd][yEnd + 1]->setDeadPiece();
        mField[xEnd][yEnd + 1] = NULL;
    }
    else if(mClickedOn->getTeam() == Piece::BLACK && mField[xEnd][yEnd - 1] != NULL)
    {
        mField[xEnd][yEnd - 1]->setDeadPiece();
        mField[xEnd][yEnd - 1] = NULL;
    }
}

void GamePlay::promote(){
    if(MoveTurn == Piece::BLACK)
    {
        mField[xEnd][yEnd] = new Queen(mField[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
        return;
    }
    renderText("PICK YOUR PIECE", 3, -1, 250);
    SDL_Surface *tmpSurface = NULL;
    if(MoveTurn == Piece::BLACK) tmpSurface = IMG_Load("src/promoteBlack.png");
    else tmpSurface = IMG_Load("src/promoteWhite.png");
    SDL_Texture *tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_Rect desRect;
    desRect.x = (WINDOW_WIDTH - 600) / 2;
    desRect.y = (WINDOW_HEIGHT - 150) / 2;
    desRect.h = 150;
    desRect.w = 600;
    SDL_RenderCopy(renderer, tmpTexture, NULL, &desRect);
    SDL_FreeSurface(tmpSurface);
    SDL_RenderPresent(renderer);
    bool promoteSuccess = false;
    while(!promoteSuccess)
    {
        SDL_WaitEvent(&event);
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_1:
                    mField[xEnd][yEnd] = new Knight(mField[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    promoteSuccess = true;
                    break;
                case SDLK_2:
                    mField[xEnd][yEnd] = new Bishop(mField[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    promoteSuccess = true;
                    break;
                case SDLK_3:
                    mField[xEnd][yEnd] = new Rook(mField[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    promoteSuccess = true;
                    break;
                case SDLK_4:
                    mField[xEnd][yEnd] = new Queen(mField[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    promoteSuccess = true;
                    break;
                default:
                    break;
            }
        }
    }
    SDL_DestroyTexture(tmpTexture);
}

void GamePlay::waitUntilKeyPress(){
    while(true)
    {
        SDL_WaitEvent(&event);
        if(event.type == SDL_KEYDOWN || event.type == SDL_QUIT || event.type == SDL_MOUSEBUTTONDOWN) return;
    }
}


//function Auto Bot
void GamePlay::manageAutoBot(){
    mDepth = 5;
    alphaBetaPrunning(mField, mDepth, INT_MIN, INT_MAX, false);
    mField[xStart][yStart]->calcPossibleMoves(mField, xStart, yStart);
    if(mField[xStart][yStart]->isValidMove(xEnd, yEnd))
    {
        mClickedOn = mField[xStart][yStart];
        mField[xStart][yStart]->PieceMove(pair<int, int>(xEnd, yEnd), mField);
        specificMove();
        mMovement = true;
        mClickedOn = NULL;
    }
}

int GamePlay::evaluate(Piece *tmpField[8][8]){
    int pawnTable[8][8] =   {
                             60, 60, 60, 60, 60, 60, 60, 60,
                             50, 50, 50, 50, 50, 50, 50, 50,
                             10, 10, 20, 30, 30, 20, 10, 10,
                              5,  5, 10, 25, 25, 10,  5,  5,
                              0,  0,  0, 20, 20,  0,  0,  0,
                              5, -5,-10,  0,  0,-10, -5,  5,
                              5, 10, 10,-20,-20, 10, 10,  5,
                              0,  0,  0,  0,  0,  0,  0,  0
                            };
    int knightTable[8][8] = {
                            -50,-40,-30,-30,-30,-30,-40,-50,
                            -40,-20,  0,  0,  0,  0,-20,-40,
                            -30,  0, 10, 15, 15, 10,  0,-30,
                            -30,  5, 15, 20, 20, 15,  5,-30,
                            -30,  0, 15, 20, 20, 15,  0,-30,
                            -30,  5, 10, 15, 15, 10,  5,-30,
                            -40,-20,  0,  5,  5,  0,-20,-40,
                            -50,-40,-30,-30,-30,-30,-40,-50
                            };
    int bishopTable[8][8] = {
                            -20,-10,-10,-10,-10,-10,-10,-20,
                            -10,  0,  0,  0,  0,  0,  0,-10,
                            -10,  0,  5, 10, 10,  5,  0,-10,
                            -10,  5,  5, 10, 10,  5,  5,-10,
                            -10,  0, 10, 10, 10, 10,  0,-10,
                            -10, 10, 10, 10, 10, 10, 10,-10,
                            -10,  5,  0,  0,  0,  0,  5,-10,
                            -20,-10,-10,-10,-10,-10,-10,-20
                            };
    int rookTable[8][8] =   {
                              0,  0,  5, 10, 10,  5,  0,  0,
                             -5,  0,  0,  0,  0,  0,  0, -5,
                             -5,  0,  0,  0,  0,  0,  0, -5,
                             -5,  0,  0,  0,  0,  0,  0, -5,
                             -5,  0,  0,  0,  0,  0,  0, -5,
                             -5,  0,  0,  0,  0,  0,  0, -5,
                              5, 10, 10, 10, 10, 10, 10,  5,
                              0,  0,  5, 10, 10,  5,  0,  0
                            };
    int queenTable[8][8] =  {
                            -20,-10,-10, -5, -5,-10,-10,-20,
                            -10,  0,  0,  0,  0,  0,  0,-10,
                            -10,  0,  5,  5,  5,  5,  0,-10,
                             -5,  0,  5,  5,  5,  5,  0, -5,
                             -5,  0,  5,  5,  5,  5,  0, -5,
                            -10,  0,  5,  5,  5,  5,  0,-10,
                            -10,  0,  0,  0,  0,  0,  0,-10,
                            -20,-10,-10, -5, -5,-10,-10,-20
                            };
    int kingTable[8][8] =   {
                            -30,-40,-40,-50,-50,-40,-40,-30,
                            -30,-40,-40,-50,-50,-40,-40,-30,
                            -30,-40,-40,-50,-50,-40,-40,-30,
                            -30,-40,-40,-50,-50,-40,-40,-30,
                            -20,-30,-30,-40,-40,-30,-30,-20,
                            -10,-20,-20,-20,-20,-20,-20,-10,
                             20, 20,  0,  0,  0,  0, 20, 20,
                             20, 30,  0,  0,  0,  0, 30, 20
                            };
    int score_white = 0;
    int score_black = 0;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(tmpField[x][y] != NULL)
            {
                switch(tmpField[x][y]->getType())
                {
                    case Piece::PAWN:
                        if(tmpField[x][y]->getTeam() == Piece::WHITE) score_white += 100 + pawnTable[x][y];
                        else score_black += 100 + pawnTable[7-y][x];
                        break;
                    case Piece::KNIGHT:
                        if(tmpField[x][y]->getTeam() == Piece::WHITE) score_white += 320 + knightTable[x][y];
                        else score_black += 320 + knightTable[7-y][x];
                        break;
                    case Piece::BISHOP:
                        if(tmpField[x][y]->getTeam() == Piece::WHITE) score_white += 330 + knightTable[x][y];
                        else score_black += 330 + bishopTable[7-y][x];
                        break;
                    case Piece::ROOK:
                        if(tmpField[x][y]->getTeam() == Piece::WHITE) score_white += 500 + rookTable[x][y];
                        else score_black += 500 + rookTable[7-y][x];
                        break;
                    case Piece::QUEEN:
                        if(tmpField[x][y]->getTeam() == Piece::WHITE) score_white += 900 + queenTable[x][y];
                        else score_black += 900 + queenTable[7-y][x];
                        break;
                    default:
                        if(tmpField[x][y]->getTeam() == Piece::WHITE)
                        {
                            kw->setCheck(tmpField, x, y, Piece::WHITE);
                            if(kw->getCheck()) score_black += 99;
                            score_white += 10000 + kingTable[x][y];
                        }
                        else
                        {
                            kb->setCheck(tmpField, x, y, Piece::BLACK);
                            if(kb->getCheck()) score_white += 50;
                            score_black += 10000 + kingTable[7-y][x];
                        }
                        break;
                }
            }
        }
    }


    return score_white - score_black;
}

int GamePlay::alphaBetaPrunning(Piece *field[8][8], int depth, int alpha, int beta, bool maximizingPlayer){
    srand(time(0));
    Piece *tmpField[8][8];
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            tmpField[x][y] = field[x][y];
        }
    }
    if(depth == 0) return evaluate(tmpField);
    if(maximizingPlayer)
    {
        if(checkEndGame(tmpField, Piece::WHITE))
        {
            return -500000;
        }
        int maxValue = INT_MIN;
        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 8; y++)
            {
                if(tmpField[x][y] != NULL && tmpField[x][y]->getTeam() == Piece::WHITE)
                {
                    tmpField[x][y]->calcPossibleMoves(tmpField, x, y);
                    vector<tuple<int, int, Piece::MoveType>> tmpPossibleMove = tmpField[x][y]->getPossibleMove();
                    for(tuple<int, int, Piece::MoveType> singleMove : tmpPossibleMove)
                    {
                        Piece *tmp1 = tmpField[x][y];
                        Piece *tmp2 = tmpField[get<0>(singleMove)][get<1>(singleMove)];

                        if(tmp2 != NULL && tmp2->getType() == Piece::KING) continue;
                        tmpField[get<0>(singleMove)][get<1>(singleMove)] = tmpField[x][y];
                        tmpField[x][y] = NULL;
                        int value = alphaBetaPrunning(tmpField, depth-1, alpha, beta, false);
                        maxValue = max(value, maxValue);
                        alpha = max(value, alpha);
                        tmpField[x][y] = tmp1;
                        tmpField[get<0>(singleMove)][get<1>(singleMove)] = tmp2;
                    }
                }
            }
            if(beta <= alpha)
            {
                break;
            }
        }
        return maxValue;
    }
    else
    {
        if(checkEndGame(tmpField, Piece::BLACK))
        {
            return 500000;
        }
        int minValue = INT_MAX;
        for(int y = 0; y < 8; y++)
        {
            for(int x = 0; x < 8; x++)
            {
                if(tmpField[x][y] != NULL && tmpField[x][y]->getTeam() == Piece::BLACK)
                {
                    tmpField[x][y]->calcPossibleMoves(tmpField, x , y);
                    vector<tuple<int, int, Piece::MoveType>> tmpPossibleMove = tmpField[x][y]->getPossibleMove();
                    for(tuple<int, int, Piece::MoveType> singleMove : tmpPossibleMove)
                    {
                        Piece *tmp1 = tmpField[x][y];
                        Piece *tmp2 = tmpField[get<0>(singleMove)][get<1>(singleMove)];
                        if(tmp2 != NULL && tmp2->getType() == Piece::KING) continue;
                        tmpField[get<0>(singleMove)][get<1>(singleMove)] = tmpField[x][y];
                        tmpField[x][y] = NULL;
                        int value = alphaBetaPrunning(tmpField, depth-1, alpha, beta, true);
                        if(value <= minValue && depth == mDepth)
                        {
                            if(value < minValue)
                            {
                                xStart = x;
                                yStart = y;
                                xEnd = get<0>(singleMove);
                                yEnd = get<1>(singleMove);
                            }
                            else if(rand()% 2)
                            {
                                xStart = x;
                                yStart = y;
                                xEnd = get<0>(singleMove);
                                yEnd = get<1>(singleMove);
                            }
                        }
                        minValue = min(value, minValue);
                        beta = min(value, beta);
                        tmpField[x][y] = tmp1;
                        tmpField[get<0>(singleMove)][get<1>(singleMove)] = tmp2;
                    }
                }
            }
            if(beta <= alpha)
            {
                break;
            }
        }
        return minValue;
    }
}


// function of updateGameStatus
void  GamePlay::changeMoveTurn(){
    if(MoveTurn == Piece::BLACK) MoveTurn = Piece::WHITE;
    else MoveTurn = Piece::BLACK;
}

void GamePlay::printCurrentMove(){
    if(mField[xEnd][yEnd]->getMoveType() == Piece::CASTLE)
    {
        if(xEnd == 2) cout << "O-O-O";
        else cout << "O-O";
    }
    else
    {
        switch(mField[xEnd][yEnd]->getType())
        {
            case 0:
                cout << "";
                break;
            case 1:
                cout << "N";
                break;
            case 2:
                cout << "B";
                break;
            case 3:
                cout << "R";
                break;
            case 4:
                cout << "Q";
                break;
            case 5:
                cout << "K";
                break;
        }
        if(mField[xEnd][yEnd]->getMoveType() == Piece::CAPTURE) cout << "x";
        switch(xEnd)
        {
            case 0:
                cout << "a" << 8 - yEnd;
                break;
            case 1:
                cout << "b" << 8 - yEnd;
                break;
            case 2:
                cout << "c" << 8 - yEnd;
                break;
            case 3:
                cout << "d" << 8 - yEnd;
                break;
            case 4:
                cout << "e" << 8 - yEnd;
                break;
            case 5:
                cout << "f" << 8 - yEnd;
                break;
            case 6:
                cout << "g" << 8 - yEnd;
                break;
            case 7:
                cout << "h" << 8 - yEnd;
                break;
        }
    }
    if (MoveTurn == Piece::BLACK)
    {
        if(kw->getCheck()) cout << "#";
        cout << endl;
    }else
    {
        if(kb->getCheck()) cout << "#";
        cout << "\t|      ";
    }
    mMovement = false;
}

bool GamePlay::checkEndGame(Piece *tmpPiece[8][8], Piece::Team currentTeam){
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if(tmpPiece[x][y] != NULL)
            {
                if(tmpPiece[x][y]->getTeam() == currentTeam)
                {
                    tmpPiece[x][y]->calcPossibleMoves(tmpPiece, x , y);
                    if(!tmpPiece[x][y]->getPossibleMove().empty())
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool GamePlay::getQuitGame(){
    return quitGame;
}

bool GamePlay::getRunning(){
    return mRunning;
}

//function of renderManage
void GamePlay::renderChessTable(){
    loadTexture(border, NULL, NULL);
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if((x + y) % 2 == 0)
            {
                if(mClickedOn != NULL && mClickedOn->isValidMove( x, y)) SDL_SetRenderDrawColor(renderer, 100, 196, 126, 1);
                else SDL_SetRenderDrawColor(renderer, 177, 212, 182, 1);
            }else
            {
                if(mClickedOn != NULL && mClickedOn->isValidMove( x, y)) SDL_SetRenderDrawColor(renderer, 0, 111, 95, 1);
                else SDL_SetRenderDrawColor(renderer, 74, 118, 103, 1);
            }
            SDL_Rect site;
            site.h = 100;
            site.w = 100;
            site.x = x * 100 + 40;
            site.y = y * 100 + 40;
            SDL_RenderFillRect(renderer, &site);
        }
    }
    kw->setCheck(mField, kw->getPossition().first, kw->getPossition().second, Piece::WHITE);
    kb->setCheck(mField, kb->getPossition().first, kb->getPossition().second, Piece::BLACK);
    if(kw->getCheck())
    {
        if((kw->getPossition().first + kw->getPossition().second) % 2 == 0)
        {
            SDL_SetRenderDrawColor(renderer, 178, 98, 63, 1);
        }else SDL_SetRenderDrawColor(renderer, 128, 55, 47, 1);
        SDL_Rect site;
        site.h = 100;
        site.w = 100;
        site.x = kw->getPossition().first * 100 + 40;
        site.y = kw->getPossition().second * 100 + 40;
        SDL_RenderFillRect(renderer, &site);
    }
    if(kb->getCheck())
    {
        if((kb->getPossition().first + kb->getPossition().second) % 2 == 0)
        {
            SDL_SetRenderDrawColor(renderer, 178, 98, 63, 1);
        }else SDL_SetRenderDrawColor(renderer, 128, 55, 47, 1);
        SDL_Rect site;
        site.h = 100;
        site.w = 100;
        site.x = kb->getPossition().first * 100 + 40;
        site.y = kb->getPossition().second * 100 + 40;
        SDL_RenderFillRect(renderer, &site);
    }
}

void GamePlay::renderText(string text, int sizeText = 3, int x = -1, int y = -1){
    SDL_Surface *tmpSurface = TTF_RenderText_Solid(tFont, text.c_str(), mTextColor);
    SDL_Texture *tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    desRect.h = tmpSurface->h * sizeText;
    desRect.w = tmpSurface->w * sizeText;
    if(x < 0)
    {
        desRect.x = (WINDOW_WIDTH - desRect.w) / 2;
    }
    else
    {
        desRect.x = x;
    }
    if(y < 0)
    {
        desRect.y = (WINDOW_HEIGHT - desRect.h) / 2;
    }
    else
    {
        desRect.y = y;
    }
    SDL_RenderCopy(renderer, tmpTexture, NULL, &desRect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(tmpSurface);
    SDL_DestroyTexture(tmpTexture);
}

void GamePlay::renderPieces(){
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(mField[x][y] != NULL && !mField[x][y]->getDeadPiece()) mField[x][y]->render(renderer);
        }
    }
}

void GamePlay::loadTexture(SDL_Surface *&surface, SDL_Rect *srcRec, SDL_Rect *desRec){
    SDL_Texture *tmpTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, tmpTexture, srcRec, desRec);
    SDL_DestroyTexture(tmpTexture);
}

void GamePlay::setTextColor(int r, int g, int b, int a){
    mTextColor.r = r;
    mTextColor.g = g;
    mTextColor.b = b;
    mTextColor.a = a;
}

//function menu game
void GamePlay::menuGame(){
    loadTexture(menu, NULL, NULL);
    desRect.w = 100;
    desRect.h = 100;
    desRect.x = 390;
    SDL_GetMouseState(&xStart, &yStart);
    mInsidePlay = false;
    mInsideMusic = false;
    mInsideExit = false;
    mInsideVsBot = false;
    mInsideVsHuman = false;
    mInsideBack = false;
    if(yStart > 470 && yStart < 530 && xStart > 390 && xStart < 490)
    {
        if(mSelectMode) mInsideVsBot = true;
        else mInsidePlay = true;
    }
    else if(yStart > 570 && yStart < 630 && xStart > 390 && xStart < 490)
    {
        if(mSelectMode) mInsideVsHuman = true;
        else mInsideMusic = true;
    }
    else if(yStart > 670 && yStart < 730 && xStart > 390 && xStart < 490)
    {
        if(mSelectMode) mInsideBack = true;
        else mInsideExit = true;
    }else
    {
        renderButton();
    }
    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            quitGame = true;
            quitMenu = true;
            mRunning = false;
        case SDL_MOUSEMOTION:
            renderButton();
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(mInsidePlay)
            {
                mSelectMode = true;
                renderButton();
            }
            else if(mInsideMusic)
            {
                if(!Mix_PlayingMusic())
                    Mix_PlayMusic(sBackground, -1);
                else
                {
                    if( Mix_PausedMusic())
                    {
                        Mix_ResumeMusic();
                    }
                    else
                    {
                        Mix_PauseMusic();
                    }
                }
                renderButton();
            }
            else if(mInsideExit)
            {
                quitMenu = true;
                quitGame = true;
                mRunning = false;
            }
            else if(mInsideVsBot)
            {
                quitGame = false;
                quitMenu = true;
                mIsOnePlayer = true;
                mSelectMode = false;
                Mix_PauseMusic();
                Mix_PlayChannel(-1, sStartGame, 0);
            }
            else if(mInsideVsHuman)
            {
                quitGame = false;
                quitMenu = true;
                mIsOnePlayer = false;
                mSelectMode = false;
                Mix_PauseMusic();
                Mix_PlayChannel(-1, sStartGame, 0);

            }
            else if(mInsideBack)
            {
                mSelectMode = false;
                renderButton();
            }
            else
            {
                renderButton();
            }
            break;
        default:
            renderButton();
            break;
    }
    renderText("CHESS GAME", 6, -1, 100);
}

void GamePlay::renderButton(){
    if(mSelectMode)
    {
        desRect.y = 450;
        if(mInsideVsBot) loadTexture(vsBotButtonInside, NULL, &desRect);
        else loadTexture(vsBotButton, NULL, &desRect);

        desRect.y = 550;
        if(mInsideVsHuman) loadTexture(vsHumanButtonInside, NULL, &desRect);
        else loadTexture(vsHumanButton, NULL, &desRect);

        desRect.y = 650;
        if(mInsideBack) loadTexture(backButtonInside, NULL, &desRect);
        else loadTexture(backButton, NULL, &desRect);
    }
    else
    {
        desRect.y = 450;
        if(mInsidePlay) loadTexture(playButtonInside, NULL, &desRect);
        else loadTexture(playButton, NULL, &desRect);

        desRect.y = 550;
        if(mInsideMusic)
        {
            if(Mix_PlayingMusic() && !Mix_PausedMusic()) loadTexture(musicButtonInside, NULL, &desRect);
            else loadTexture(musicButtonOffInside, NULL, &desRect);
        }
        else
        {
            if(Mix_PlayingMusic() && !Mix_PausedMusic()) loadTexture(musicButton, NULL, &desRect);
            else loadTexture(musicButtonOff, NULL, &desRect);
        }

        desRect.y = 650;
        if(mInsideExit) loadTexture(exitButtonInside, NULL, &desRect);
        else loadTexture(exitButton, NULL, &desRect);
    }
}

bool GamePlay::getQuitMenu(){
    return quitMenu;
}
