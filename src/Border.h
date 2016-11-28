#ifndef BORDER_H
#define BORDER_H

#include "GameObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Border : public GameObject
{
public:
    Border(int x_p, int y_p,int w, int h, SDL_Renderer* render, TextureManager* mngr);

    void willCollide(std::vector<GameObject*> const& objects);
    void update(float const& deltaTime);

private:
    void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects);

};

#endif