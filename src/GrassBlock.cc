#include "GrassBlock.h"

/**
 * @brief Constructor for GrassBlock
 *
 * @param xPos x position of block
 * @param yPos y position of block
 * @param render renderer to draw to
 * @param mngr texture manager to use with sprite
 */
GrassBlock::GrassBlock(int x_pos, int y_pos, SDL_Renderer* render, TextureManager* mngr)
        : Block(x_pos, y_pos, 152, 37, 1, "./images/new_grass.png", render, mngr)
{
    type = "block";
}
