#include "FallBlock.h"

/**
 * @brief Constructor for FallBlock
 *
 * @param xPos x position of block
 * @param yPos y position of block
 * @param render renderer to draw to
 * @param acti states if block is activatable by player
 * @param mngr texture manager to use with sprite
 */
FallBlock::FallBlock(int x_pos, int y_pos, SDL_Renderer* render,bool acti,TextureManager* mngr)
        : ActiveBlock(x_pos, y_pos, 152, 37, 1, "./images/new_grass.png", render, mngr), activatable{acti}
{
    if (activatable)
    {
        type = "fallblock";
    }
    else
    {
        type = "block";
    }
}

/**
 * @brief Activator for FallBlock
 *
 * Makes the block active and changes its type to the intended one
 */
void FallBlock::activate()
{
    active = true;
    type = "fallingblock";
}

/**
 * @brief Updator for FallBlock
 *
 * Makes the block fall if it's active
 */
void FallBlock::update(float const& deltaTime)
{
    if (active)
    {
        updatePosition();
        sprite -> spriteRect.y += 205 * deltaTime;
    }
}
