#ifndef SKELETRONPROJECTILE_H
#define SKELETRONPROJECTILE_H

#include <random>

#include "Projectile.h"
#include "GameObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SkeletronProjectile : public Projectile
{
public:
    SkeletronProjectile(int x, int y, int dirX, int dirY, SDL_Renderer* render, GameObject* creator_ptr, TextureManager* mngr);

private:
    void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects);
    std::random_device rnd;
    std::uniform_int_distribution<int> randomYBuffer{1, 3};
    int bounces{0};
};

#endif