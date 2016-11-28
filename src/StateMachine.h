#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "GameState.h"
#include "PlayState.h"
#include "MenuState.h"
#include "DeathState.h"


class StateMachine
{
public:
    void init();
    ~StateMachine();

    void changeState(GameState* state);
    GameState* getCurrentState();
    void update();

private:
    void TransferStateValues(GameState* NextCurrentState);
    std::vector<GameState*> states;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    GameState* play = nullptr;
    GameState* menu = nullptr;
    GameState* endmenu = nullptr;
    GameState* currentState = nullptr;
};

#endif /*STATEMACHINE_H*/