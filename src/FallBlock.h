#ifndef FALLBLOCK_H
#define FALLBLOCK_H

#include "GameObject.h"
#include "Block.h"
#include "ActiveBlock.h"

class FallBlock : public ActiveBlock
{
public:
    FallBlock(int x_pos, int y_pos, SDL_Renderer* render, bool acti, TextureManager* mngr);

    void activate();
    void update(float const& deltaTime);

private:
    bool activatable;
};

#endif