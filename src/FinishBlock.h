#ifndef FINISH_H
#define FINISH_H

#include "GameObject.h"
#include "Block.h"
#include "ActiveBlock.h"

class FinishBlock : public ActiveBlock
{
public:
    FinishBlock(int x_pos, int y_pos, SDL_Renderer* render, int visibleOnStart, TextureManager* mngr);

    void activate();
    void deActivate();

private:
    bool active;
};

#endif