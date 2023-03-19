#include <iostream>
#include "GamePlay.h"

using namespace std;

int main(int argc, char* argv[])
{
    GamePlay *chess = new GamePlay;

    if(chess->initWindow())
    {
        chess->startPos();
        chess->initMoveTurn();
        while(true)
        {
            chess->handle();
            chess->render();
            chess->update();
            chess->sound();
            if(!chess->running()) break;
        }
    }
    chess->clean();
    return 0;
}
