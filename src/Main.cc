#include <iostream>
#include <SDL2/SDL.h>
#include "StateMachine.h"

using namespace std;

int main()
{
    StateMachine game;
    game.init();
    SDL_Quit();
    return 0;
}
