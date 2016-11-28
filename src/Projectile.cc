#include "Projectile.h"

/**
 * @brief Constructor for GameObject
 *
 * @param x_p x position of block
 * @param y_p y position of block
 * @param w width of block
 * @param h height of block
 * @param amountOfFrames amount of frames in blocks spritesheet
 * @param spriteSheet location of spritesheet
 * @param render renderer to draw to
 * @param dir direction to spawn the projectile in
 * @param creator_ptr pointer to object that created projectile
 * @param mngr texture manager to use with sprite
 */
Projectile::Projectile(int x_p, int y_p, int w, int h, int amountOfFrames, std::string spriteSheet, SDL_Renderer* render, int dir, GameObject* creator_ptr, TextureManager* mngr)
: GameObject(x_p, y_p, w, h, amountOfFrames, spriteSheet, render, mngr)
{
    direction = dir;
    setXVel(6 * direction);
    type = "projectile";
    creator = creator_ptr;
}

Projectile::~Projectile(){ }

void Projectile::handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> /*collidingObjects*/) { }

/**
 * @brief Updator for Projecile
 *
 * Resets collision during this update bool.
 * Updates position of projectile.
 */
void Projectile::update(float const& /*deltaTime*/)
{
    collidedThisUpdate = false;
    sprite -> spriteRect.x += xVel;
    sprite -> spriteRect.y += yVel;
}

/**
 * @brief Checks for collision with every object on the screen and handles it if collision has occurred.
 *
 * Creates a vector that will contain the object and the type of the object it collides with.
 * Creates a vector with the resulting collision direction of the object it collides with.
 * Loops through all objects on screen and checks for collision.
 * Calls handleCollision() with the previously mentioned vector containing the object and its type.
 */
void Projectile::willCollide(std::vector<GameObject*> const& objects)
{
    std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collided_types;
    std::array<std::string, 4> result;
    for (GameObject* object : objects)
    {
        if (object != this && intersect(object, result))
        {
            collided_types.push_back(std::make_pair(object, result));
        }
    }
    return handleCollision(collided_types);
}