#ifndef GRASSBLOCK_H
#define GRASSBLOCK_H

#include "Block.h"
#include "GameObject.h"

class GrassBlock : public Block
{
public:
    GrassBlock(int x_pos, int y_pos, SDL_Renderer* render, TextureManager* mngr);

private:
};

#endif