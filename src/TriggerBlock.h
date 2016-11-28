#ifndef TRIGGERBLOCK_H
#define TRIGGERBLOCK_H

#include "GameObject.h"
#include "Block.h"
#include "ActiveBlock.h"

class TriggerBlock : public ActiveBlock
{
public:
    TriggerBlock(int x_pos, int y_pos, SDL_Renderer* renderer, ActiveBlock* target_obj, TextureManager* mngr);
    ~TriggerBlock();

    void activate();

private:
    ActiveBlock* target;
};

#endif