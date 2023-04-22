#include <iostream>
#include "GamePlay.h"

using namespace std;

int main(int argc, char* argv[])
{
    GamePlay *chess = new GamePlay;

    if(chess->initWindow())
    {
        while(!chess->quitMenu)
        {
            chess->menuGame();
        }
        chess->sound();
        while(chess->running())
        {
            chess->handleEvent();
            chess->renderAll();
            chess->updateConditional();
        }
    }
    chess->clean();
    return 0;
}
