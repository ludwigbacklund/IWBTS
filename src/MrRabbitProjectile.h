#ifndef MRRABBITPROJECTILE_H
#define MRRABBITPROJECTILE_H

#include "Projectile.h"
#include "GameObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class MrRabbitProjectile : public Projectile
{
public:
    MrRabbitProjectile(int x, int y, int dir, SDL_Renderer *render, GameObject *creator_ptr, TextureManager* mngr);

private:
    void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects);
};

#endif