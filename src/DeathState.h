#ifndef DEATHSTATE_H
#define DEATHSTATE_H

#include "GameState.h"
#include <vector>
#include "Button.h"

class DeathState : public GameState
{
public:
    DeathState(SDL_Window* win, SDL_Renderer* rend);
    ~DeathState();

    void init();

    void update(float const& deltaTime);
    void handle(SDL_Event event, float deltaTime);
};

#endif /* DEATHSTATE_H */