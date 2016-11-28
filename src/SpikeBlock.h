#ifndef SPIKEBLOCK_H
#define SPIKEBLOCK_H

#include "GameObject.h"
#include "Block.h"
#include "ActiveBlock.h"

class SpikeBlock : public ActiveBlock
{
public:
    SpikeBlock(int x_pos, int y_pos, SDL_Renderer* renderer, int acti, TextureManager* mngr);

    void activate();
    void deActivate();
};

#endif