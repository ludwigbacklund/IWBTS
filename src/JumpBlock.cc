#include "JumpBlock.h"

/**
 * @brief Constructor for JumpBlock
 *
 * @param xPos x position of block
 * @param yPos y position of block
 * @param render renderer to draw to
 * @param mngr texture manager to use with sprite
 */
JumpBlock::JumpBlock(int x_pos, int y_pos, SDL_Renderer* render, TextureManager* mngr)
        : ActiveBlock(x_pos, y_pos, 16, 16, 1, "./images/jumpblock.png", render, mngr)
{
    type = "jumpblock";
}

void JumpBlock::activate() { }

