#include "PlayerProjectile.h"

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
PlayerProjectile::PlayerProjectile(int x, int y, int dir, SDL_Renderer* render, GameObject* creator_ptr, TextureManager* mngr)
        : Projectile(x, y, 15, 9, 4, "./images/rock_proj.png", render, dir, creator_ptr, mngr)
{
    sprite -> setAnimationStartIndex(0);
    sprite -> setAnimationEndIndex(3);
}

/**
 * @brief Collision handler for PlayerProjectile
 *
 * Loops through all colliding objects.
 * Gets the type of the colliding object.
 * If the object is a block the projectile should die next update.
 * If the object is an enemy it should incur damage on it and then die next update.
 */
void PlayerProjectile::handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects)
{
    for (auto object : collidingObjects)
    {
        std::string obj_type = object.first -> getType();
        if (obj_type == "block")
        {
            dieNextUpdate = true;
        }
        if (obj_type == "enemy")
        {
            object.first -> takeDmg();
            dieNextUpdate = true;
        }
    }
}