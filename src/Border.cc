#include "Border.h"

/**
 * @brief Constructor for Border
 *
 * @param x_p x position of block
 * @param y_p y position of block
 * @param w width of block
 * @param h height of block
 * @param render renderer to draw to
 * @param mngr texture manager to use with sprite
 */
Border::Border(int x_p, int y_p,int w, int h, SDL_Renderer* render, TextureManager* mngr)
: GameObject(x_p, y_p, w, h, 1, "", render, mngr)
{
    type = "border";
}

void Border::handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> /*collidingObjects*/) { }

void Border::willCollide(std::vector<GameObject*> const& /*objects*/) { }

void Border::update(float const& /*deltaTime*/) { }

