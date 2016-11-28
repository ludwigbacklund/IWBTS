#include "Checkpoint.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @brief Constructor for Checkpoint
 *
 * @param xPos x position of checkpoint
 * @param yPos y position of checkpoint
 * @renderer renderer to draw to
 * @param mngr texture manager to use with sprite
 */
Checkpoint::Checkpoint(int x_pos, int y_pos, SDL_Renderer* renderer, TextureManager* mngr)
        : GameObject(x_pos, y_pos, 9, 14, 4, "./images/checkpointcompressed.png", renderer,mngr)
{
    type = "checkpoint";
}

Checkpoint::~Checkpoint() { }

void Checkpoint::handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> /*collidingObjects*/) { }

void Checkpoint::update(float const& /*deltaTime*/) { }

void Checkpoint::willCollide(std::vector<GameObject*> const& /*objects*/) { }