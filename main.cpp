#include <iostream>
#include "GamePlay.h"

using namespace std;

int main(int argc, char* argv[])
{
    GamePlay *chess = new GamePlay;

    if(chess->initWindow())
    {
        chess->startPos();
        chess->sound();
        while(true)
        {
            chess->handle();
            chess->render();
            chess->update();
            if(!chess->running()) break;
        }
    }
    SDL_Delay(5000)
;    chess->clean();
    return 0;
}
