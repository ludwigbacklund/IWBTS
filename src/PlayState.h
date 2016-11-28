#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"

class PlayState : public GameState
{
public:
    PlayState(SDL_Window* win, SDL_Renderer* rend);
    ~PlayState();

    void init();
    
    void loadLevel(std::string level);
    void createObject(std::string name, int x, int y, int extra,std::string path, SDL_Renderer* renderer);
    void update(float const& deltaTime);
    void handle(SDL_Event event, float deltaTime);
};

#endif /* PLAYSTATE_H */