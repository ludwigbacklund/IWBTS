#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <vector>
#include "GameObject.h"
#include "TextureManager.h"

class GameState
{
public:
    virtual void init() = 0;
    virtual ~GameState(){}

    virtual void update(float const& deltaTime) = 0;
    virtual void handle(SDL_Event event, float deltaTime) = 0;

    std::string level{""};
    int nextState{};
    bool pause{false};
    int playerX{0};
    int playerY{0};

protected:
    Sprite* background;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::vector<GameObject*> objects;
    TextureManager* mngr{new TextureManager()};

};

#endif /* GAMESTATE_H */