#include "SpikeBlock.h"
/**
 * @brief Constructor for SpikeBlock
 *
 * @param xPos x position of block
 * @param yPos y position of block
 * @param render renderer to draw to
 * @param active If the object should be visible at start
 * @param mngr texture manager to use with sprite
 */
SpikeBlock::SpikeBlock(int x_pos, int y_pos, SDL_Renderer* renderer, int acti, TextureManager* mngr)
        : ActiveBlock(x_pos, y_pos, 56, 10, 1, "./images/spikes.png", renderer, mngr)
{
    active = static_cast<bool>(acti);
    if (active)
    {
        sprite->spriteRect.w = 56;
        sprite->spriteRect.h = 10;
        type = "spikeblock";
    }
    else
    {
        deActivate();
    }
}

/**
 * @brief Activate for SpikeBlock
 *
 * If the object at creation was set to be invisible, triggering via triggerblock will show it.
 * If the object at creation was set to be visible, call deActivate function.
 *
 */
void SpikeBlock::activate()
{
    if (!active)
    {
        sprite->spriteRect.w = 56;
        sprite->spriteRect.h = 10;
        type = "spikeblock";
    }
    else
    {
        deActivate();
    }
}

/**
 * @brief Hides the SpikeBlock
 *
 */
void SpikeBlock::deActivate()
{
    sprite -> spriteRect.w = 0;
    sprite -> spriteRect.h = 0;
    type = "Unactivespikeblock";
}