#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Projectile : public GameObject
{
public:
    Projectile(int x_p, int y_p,int w, int h,int amountOfFrames, std::string spriteSheet, SDL_Renderer* render, int dir, GameObject* creator_ptr, TextureManager* mngr);
    ~Projectile();

    virtual void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects);
    void update(float const& deltaTime);
    void willCollide(std::vector<GameObject*> const& objects);

private:
    GameObject* creator;
};

#endif