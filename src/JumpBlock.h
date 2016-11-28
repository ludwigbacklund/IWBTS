#include "Block.h"
#include "ActiveBlock.h"

class JumpBlock : public ActiveBlock
{
public:
    JumpBlock(int x_pos, int y_pos, SDL_Renderer* render, TextureManager* mngr);

    void activate();
};