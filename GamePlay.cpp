#include "GamePlay.h"

using namespace std;

GamePlay::GamePlay(){
    isRunning = true;
    xStart = -1;
    yStart = -1;
    xEnd = -1;
    yEnd = -1;
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

    MoveTurn = Piece::WHITE;
    Movement = false;
}

GamePlay::~GamePlay(){
    //dtor
}

bool GamePlay::initWindow(){
    WINDOW_HEIGHT = 800;
    WINDOW_WIDTH = 800;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        //cerr << "SDL INIT FAIL! ERROR LOG: " << SDL_GetError() << endl;
        return false;
    }else
    {
        window = SDL_CreateWindow("CHESS GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
         if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            //cerr << "MIXER CREATE FAIL! ERROR LOG: " << SDL_GetError() << endl;
            return false;
        }
        if (TTF_Init() < 0)
        {
            //cerr << "TTF CREATE FAIL! ERROR LOG: " << SDL_GetError() << endl;
            return false;
        }
        if(window == NULL)
        {
            //cerr << "WINDOW CREATE FAIL! ERROR LOG: " << SDL_GetError() << endl;
            return false;
        }else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL)
            {
                //cerr << "RENDERER CREATE FAIL! ERROR LOG: " << SDL_GetError() << endl;
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

    tFont = TTF_OpenFont("font/Silkscreen-Regular.ttf", 20);

    gameStart = true;
    currentMove = Piece::STATIONARY;
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
    kw->setCheck(field, kw->getPossition().first, kw->getPossition().second, Piece::WHITE);
    kb->setCheck(field, kb->getPossition().first, kb->getPossition().second, Piece::BLACK);
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

void GamePlay::renderText(string text, int x, int y, int sizeText = 3){
    SDL_Surface *tmpSurface = TTF_RenderText_Solid(tFont, text.c_str(), textColor);
    SDL_Texture *tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_Rect desRect;
    desRect.h = tmpSurface->h * sizeText;
    desRect.w = tmpSurface->w * sizeText;
    desRect.x = x;
    desRect.y = y;
    SDL_RenderCopy(renderer, tmpTexture, NULL, &desRect);
    SDL_FreeSurface(tmpSurface);
    SDL_RenderPresent(renderer);
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

int GamePlay::evaluate(Piece *tmpField[8][8])
{
    int score_base[8][8] = {0, 1, 3, 4, 4, 3, 1, 0,
                            1, 3, 4, 5, 5, 4, 3, 1,
                            1, 4, 5, 7, 7, 5, 4, 1,
                            2, 5, 7, 9, 9, 7, 5, 2,
                            2, 5, 7, 9, 9, 7, 5, 2,
                            1, 4, 5, 7, 7, 5, 4, 1,
                            1, 3, 4, 5, 5, 4, 3, 1,
                            0, 1, 3, 4, 4, 3, 1, 0};
    int score_white = 0;
    int score_black = 0;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {

            if(tmpField[x][y] != NULL)
            {
                int score = 0;
                switch(tmpField[x][y]->getType())
                {
                    case Piece::PAWN:
                        score = 10;
                        break;
                    case Piece::KNIGHT:
                        score = 30;
                        break;
                    case Piece::BISHOP:
                        score = 30;
                        break;
                    case Piece::ROOK:
                        score = 50;
                        break;
                    case Piece::QUEEN:
                        score = 90;
                        break;
                    default:
                        score = 10000;
                        break;
                }
                if(tmpField[x][y]->getTeam() == Piece::WHITE) score_white += score + score_base[x][y];
                else score_black += score + score_base[x][y];
            }
        }
    }
    return score_white - score_black;
}

int GamePlay::alphaBetaPrunning(Piece *field[8][8], int depth, int alpha, int beta, bool maximizingPlayer)
{
    Piece *tmpField[8][8];
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            tmpField[x][y] = field[x][y];
        }
    }
    //cerr << "begin" << endl;
    Piece::Team currentTeam = Piece::BLACK;
    if(maximizingPlayer) currentTeam = Piece::WHITE;
    else currentTeam = Piece::BLACK;
    if(depth == 0 || checkEndGame(tmpField, currentTeam)) return evaluate(tmpField);
    //cerr << "begin" << endl;

    if(maximizingPlayer)
    {
        //cerr << depth << "trang" << endl;
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
                        //cerr << tmpField[x][y]->getType() << "piece pos: " << x << "  " << y << "  ";
                        //cerr << "piece move to " << get<0>(singleMove) << "  " << get<1>(singleMove) << endl;
                        Piece *tmp1 = field[x][y];
                        Piece *tmp2 = field[get<0>(singleMove)][get<1>(singleMove)];

                        if(tmp2 != NULL && tmp2->getType() == Piece::KING) continue;
                        tmpField[get<0>(singleMove)][get<1>(singleMove)] = tmpField[x][y];
                        tmpField[x][y] = NULL;
                        //cerr << "half done" << endl;
                        int value = alphaBetaPrunning(tmpField, depth-1, alpha, beta, false);
                        maxValue = max(value, maxValue);
                        alpha = max(value, alpha);
                        tmpField[x][y] = tmp1;
                        tmpField[get<0>(singleMove)][get<1>(singleMove)] = tmp2;
                        //cerr << "done" << endl;
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
        //cerr << depth << "den" << endl;
        int minValue = INT_MAX;
        for(int y = 0; y < 8; y++)
        {
            for(int x = 0; x < 8; x++)
            {
                ////cerr << x << "  " << y << endl;
                if(tmpField[x][y] != NULL && tmpField[x][y]->getTeam() == Piece::BLACK)
                {
                    tmpField[x][y]->calcPossibleMoves(tmpField, x , y);
                    vector<tuple<int, int, Piece::MoveType>> tmpPossibleMove = tmpField[x][y]->getPossibleMove();
                    for(tuple<int, int, Piece::MoveType> singleMove : tmpPossibleMove)
                    {
                        //cerr << tmpField[x][y]->getType() << "piece pos: " << x << "  " << y << "  ";
                        //cerr << "piece move to " << get<0>(singleMove) << "  " << get<1>(singleMove) << endl;
                        Piece *tmp1 = field[x][y];
                        Piece *tmp2 = field[get<0>(singleMove)][get<1>(singleMove)];
                        if(tmp2 != NULL && tmp2->getType() == Piece::KING) continue;
                        tmpField[get<0>(singleMove)][get<1>(singleMove)] = tmpField[x][y];
                        tmpField[x][y] = NULL;
                        //cerr << "half done" << endl;
                        int value = alphaBetaPrunning(tmpField, depth-1, alpha, beta, true);
                        if(value < minValue && depth == mDepth)
                        {
                            xStart = x;
                            yStart = y;
                            xEnd = get<0>(singleMove);
                            yEnd = get<1>(singleMove);
                            ////cerr << value << " ";
                        }
                        minValue = min(value, minValue);
                        beta = min(value, beta);
                        tmpField[x][y] = tmp1;
                        tmpField[get<0>(singleMove)][get<1>(singleMove)] = tmp2;
                        //cerr << "done" << endl;
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

void GamePlay::handle(){
    mDepth = 3;
    if(MoveTurn == Piece::BLACK)
    {
        alphaBetaPrunning(field, mDepth, INT_MIN, INT_MAX, false);
        //cout << xStart << "  " << yStart;
        if(field[xStart][yStart] != NULL)field[xStart][yStart]->PieceMove(pair<int, int>(xEnd, yEnd), field);
        changeMoveTurn();
    }

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
                field[xStart][yStart]->calcPossibleMoves(field, xStart, yStart);
            }
        }
        else if(event.type == SDL_MOUSEBUTTONUP && field[xStart][yStart] != NULL && field[xStart][yStart]->getTeam() == MoveTurn)
        {
            SDL_GetMouseState(&xEnd, &yEnd);
            xEnd /= 100;
            yEnd /= 100;
            if(field[xStart][yStart]->isValidMove( xEnd, yEnd))
            {
                field[xStart][yStart]->PieceMove(pair<int, int>(xEnd, yEnd), field);
                specificMove();
                if(xStart != xEnd || yStart != yEnd)
                {
                    Movement = true;
                    clickedOn = NULL;
                }
            }else clickedOn = NULL;
        }
}

void GamePlay::specificMove(){
    if(clickedOn->getMoveType() == Piece::CASTLE) castle();
    else if(clickedOn->getMoveType() == Piece::ENPASSANT) enpassant();
    else if(clickedOn->getMoveType() == Piece::PROMOTE) promote();
    clickedOn->declineEnpassant(field);
    sound(clickedOn->getMoveType());
}

void GamePlay::castle(){
    if(xEnd == 6)
    {
        field[xEnd + 1][yEnd]->PieceMove(pair<int, int>(xEnd - 1,yEnd), field);
    }
    if(xEnd == 2)
    {
        field[xEnd - 2][yEnd]->PieceMove(pair<int, int>(xEnd + 1,yEnd), field);
    }
}

void GamePlay::enpassant(){
    if(clickedOn->getTeam() == Piece::WHITE && field[xEnd][yEnd + 1] != NULL)
    {
        field[xEnd][yEnd + 1]->isDead = true;
        field[xEnd][yEnd + 1] = NULL;
    }
    else if(clickedOn->getTeam() == Piece::BLACK && field[xEnd][yEnd - 1] != NULL)
    {
        field[xEnd][yEnd - 1]->isDead = true;
        field[xEnd][yEnd - 1] = NULL;
    }
}

void GamePlay::promote(){
    renderText("PICK YOUR PIECE", 100, 250);
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
                    field[xEnd][yEnd] = new Knight(field[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    promoteSuccess = true;
                    break;
                case SDLK_2:
                    field[xEnd][yEnd] = new Bishop(field[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    promoteSuccess = true;
                    break;
                case SDLK_3:
                    field[xEnd][yEnd] = new Rook(field[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    promoteSuccess = true;
                    break;
                case SDLK_4:
                    field[xEnd][yEnd] = new Queen(field[xEnd][yEnd]->getTeam(), pair<int, int>(xEnd, yEnd));
                    promoteSuccess = true;
                    break;
                default:
                    break;
            }
        }
    }
    SDL_DestroyTexture(tmpTexture);
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

bool GamePlay::checkEndGame(Piece *tmpPiece[8][8], Piece::Team currentTeam){
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if(tmpPiece[x][y] != NULL)
            {
                if(tmpPiece[x][y]->getTeam() == currentTeam)
                {
                    //cerr << x << "  " << y << endl;
                    tmpPiece[x][y]->calcPossibleMoves(tmpPiece, x , y);
                    //cerr << "here" << endl;
                    if(!tmpPiece[x][y]->getPossibleMove().empty())
                    {
                        //cerr << "returned" << endl;
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void GamePlay::sound(Piece::MoveType soundType){
    if(gameStart)
    {
        Mix_PlayChannel(-1, sStartGame, 0);
        gameStart = false;
    }
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
    if(checkEndGame(field, MoveTurn))
    {
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
    if(checkEndGame(field, MoveTurn))
    {
        isRunning = false;
        if(MoveTurn == Piece::BLACK) renderText("WHITE IS WINNWER", 50, 300, 3);
        else renderText("BLACK IS WINNWER", 50, 300, 3);
        sound();
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
