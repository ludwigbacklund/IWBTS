#include "FinishBlock.h"

/**
 * @brief Constructor for Continuator class
 *
 * @param x_pos x position of continuator
 * @param y_pos y position of continuator
 * @param render renderer to draw to
 * @param extra specifies visibility from start of game
 * @param mngr texture manager to use with sprite
 */
FinishBlock::FinishBlock(int x_pos, int y_pos, SDL_Renderer* render, int extra, TextureManager* mngr)
        : ActiveBlock(x_pos, y_pos, 30, 30, 1, "./images/Coin1.png", render, mngr), active{static_cast<bool>(extra)}
{
    if (active)
    {
        activate();
    }
    else
    {
        deActivate();
    }
}

void FinishBlock::activate()
{
    type = "finish";
    sprite -> spriteRect.w = 30;
    sprite -> spriteRect.w = 30;
}

void FinishBlock::deActivate()
{
    sprite -> spriteRect.w = 0;
    sprite -> spriteRect.w = 0;
    type = "Inactive";

}