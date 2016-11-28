#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H

#include "Projectile.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class PlayerProjectile : public Projectile
{
public:
    PlayerProjectile(int x, int y, int dir, SDL_Renderer* render, GameObject* creator_ptr, TextureManager* mngr);

private:
    void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects);
};

#endif