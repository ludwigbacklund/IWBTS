#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"

class Block : public GameObject
{
public:
    Block(int x_p, int y_p,int w, int h,int amountOfFrames, std::string spriteSheet, SDL_Renderer* render, TextureManager* mngr);
    ~Block();

    virtual void update(float const& deltaTime);
    void willCollide(std::vector<GameObject*> const& objects);

private:
    void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects);
};

#endif