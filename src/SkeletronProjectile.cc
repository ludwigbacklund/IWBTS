#include "SkeletronProjectile.h"

/**
 * @brief Constructor for SkeletronProjectile
 *
 * @param x x position of projectile
 * @param y y position of projectile
 * @param dirX x direction to spawn projectile in
 * @param dirY y direction to spawn projectile in
 * @param render renderer to draw to
 * @param creator_ptr pointer to object that created projectile
 * @param mngr texture manager to use with sprite
 */
SkeletronProjectile::SkeletronProjectile(int x, int y, int dirX, int dirY, SDL_Renderer *render, GameObject *creator_ptr, TextureManager* mngr)
        :Projectile(x, y, 17, 13, 4, "./images/fireballcompressed.png", render, dirX, creator_ptr, mngr)
{
    setYVel(randomYBuffer(rnd) * dirY);
    sprite -> setAnimationStartIndex(0);
    sprite -> setAnimationEndIndex(3);
}

/**
 * @brief Collision handler for SkeletronProjectile
 *
 * Loops through colliding objects.
 * Gets type of colliding object.
 * If object is a block or a border it bounces of it
 * If the projectile has bounced more than seven times it dies instead.
 * If the object is a player it incurs damage on it and dies next update.
 */
void SkeletronProjectile::handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects)
{
    for (auto object : collidingObjects)
    {
        std::string obj_type = object.first -> getType();
        if (!collidedThisUpdate && (obj_type == "block" || obj_type == "border"))
        {
            collidedThisUpdate = true;
            bounces += 1;
            if (object.second[2] == "left_x")
            {
                setXVel(getXVel() * -1);
                direction = -1;
            }
            if (object.second[3] == "right_x")
            {
                setXVel(getXVel() * 1);
                direction = 1;
            }
            if (object.second[1] == "bot_y")
            {
                setYVel(getYVel() * -1);
            }
            if (object.second[0] == "top_y")
            {
                setYVel(getYVel() * -1);
                
            }
            if (bounces > 7)
            {
                kill();
            }
        }
        if (obj_type == "player")
        {
            object.first -> takeDmg();
            dieNextUpdate = true;
        }
    }
}