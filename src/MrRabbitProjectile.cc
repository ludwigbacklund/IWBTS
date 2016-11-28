#include "MrRabbitProjectile.h"

/**
 * @brief Constructor for PlayerProjectile
 *
 * @param x x position of projectile
 * @param y y position of projectile
 * @param dir direction the projectile spawns in
 * @param render renderer to draw to
 * @param creator_ptr pointer to the object that created the projectile
 * @param mngr texture manager to use with sprite
 */
MrRabbitProjectile::MrRabbitProjectile(int x, int y, int dir, SDL_Renderer *render, GameObject *creator_ptr, TextureManager* mngr)
        : Projectile(x, y, 16, 6, 1, "./images/carrot.png", render, dir, creator_ptr, mngr) { }

/**
 * @brief Collision handler for MrRabbitProjectile
 *
 * Loops through all objects it has collided with.
 * Gets the type of the colliding object.
 * Dies next update if the object is a block.
 * If object is a player it incurs damage on player and dies next update.
 */
void MrRabbitProjectile::handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects)
{
    for (auto object : collidingObjects)
    {
        std::string obj_type = object.first -> getType();
        if (obj_type == "block")
        {
            dieNextUpdate = true;
        }
        if (obj_type == "player")
        {
            object.first -> takeDmg();
            dieNextUpdate = true;
        }
    }
}