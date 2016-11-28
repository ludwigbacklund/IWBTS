#include "TriggerBlock.h"
#include "ActiveBlock.h"

/**
 * @brief Constructor for TriggerBlock
 *
 * @param xPos x position of block
 * @param yPos y position of block
 * @param render renderer to draw to
 * @param target_obj Pointer to object which the trigger will activate.
 * @param mngr texture manager to use with sprite
 */
TriggerBlock::TriggerBlock(int x_pos, int y_pos, SDL_Renderer* renderer, ActiveBlock* target_obj, TextureManager* mngr)
        : ActiveBlock(x_pos, y_pos, 16, 4, 1, "./images/triggerblock.png", renderer, mngr), target{target_obj}
{
    type = "triggerblock";

}

/**
 * @brief destructor for TriggerBlock
 *
 * Triggerblock should not be responsible for removing its target
 * Target removal will be handled by playstate
 */
TriggerBlock::~TriggerBlock() {}

/**
 * @brief Activator for TriggerBlock
 * Calls the target objects activate function
 */
void TriggerBlock::activate()
{
    target -> activate();
}

