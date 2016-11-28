#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include <vector>
#include "Button.h"

class MenuState : public GameState
{
public:
    MenuState(SDL_Window* win, SDL_Renderer* rend);
    ~MenuState();

    void init();

    void update(float const& deltaTime);
    void handle(SDL_Event event, float deltaTime);
    std::vector<Button*> menuItems;
};

#endif /* MENUSTATE_H */