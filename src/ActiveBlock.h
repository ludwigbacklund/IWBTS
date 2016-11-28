#ifndef ACTIVEBLOCK_H
#define ACTIVEBLOCK_H

#include "GameObject.h"
#include "Block.h"

class ActiveBlock : public Block
{
public:
    ActiveBlock(int x_p, int y_p, int w, int h, int amountOfFrames, std::string spriteSheet, SDL_Renderer* render, TextureManager* mngr);

    virtual void activate() = 0;

protected:
    bool active{false};
};

#endif