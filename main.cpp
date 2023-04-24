#include <iostream>
#include "GamePlay.h"

using namespace std;

int main(int argc, char* argv[])
{
    GamePlay *chess = new GamePlay;
    if(chess->initGameData())
    {
        while(chess->getRunning())
        {
            chess->setNewGame();
            while(!chess->getQuitMenu())
            {
                chess->menuGame();
            }
            if(!chess->getQuitGame()) chess->setNewGame();
            while(!chess->getQuitGame())
            {
                chess->handleEventInGame();
                chess->renderManage();
                chess->updateGameStatus();
            }
        }
    }
    chess->clean();
    return 0;
}
