#include <iostream>
#include "GamePlay.h"

using namespace std;

int main(int argc, char* argv[])
{
    GamePlay *chess = new GamePlay;

    if(chess->initWindow())
    {
        chess->sound();
        while(true)
        {
            chess->handleEvent();
            chess->renderAll();
            chess->updateConditional();
            if(!chess->running()) break;
        }
    }
    chess->waitUntilKeyPress();
    chess->clean();
    return 0;
}
