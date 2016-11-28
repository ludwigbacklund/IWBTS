#include "Enemy.h"

/**
 * @brief Constructor for ActiveBlock
 *
 * @param x_p x position of block
 * @param y_p y position of block
 * @param w width of block
 * @param h height of block
 * @param amountOfFrames amount of frames in blocks spritesheet
 * @param spriteSheet location of spritesheet
 * @param render renderer to draw to
 * @param player_ptr Pointer to the active player
 * @param mngr texture manager to use with sprite
 */
Enemy::Enemy(int x_p, int y_p, int w, int h, int amountOfFrames, std::string spriteSheet, SDL_Renderer* render, Player* player_ptr, TextureManager* mngr)
: GameObject(x_p, y_p, w, h, amountOfFrames, spriteSheet, render, mngr), player{player_ptr}
{
    type = "enemy";
}

Enemy::~Enemy() { }

/**
 * @brief Moves to the left
 *
 * Updates objects x position to move left on the game screen
 */
void Enemy::moveLeft()
{
   sprite -> spriteRect.x += -1;
}

/**
 * @brief Moves to the right
 *
 * Updates objects x position to move right on the game screen
 */
void Enemy::moveRight()
{
    sprite -> spriteRect.x += 1;
}