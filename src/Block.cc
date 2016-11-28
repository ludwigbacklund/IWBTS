#include "Block.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
 * @param mngr texture manager to use with sprite
 */
Block::Block(int x_p, int y_p,int w, int h,int amountOfFrames, std::string spriteSheet, SDL_Renderer* render, TextureManager* mngr)
: GameObject(x_p, y_p, w, h, amountOfFrames, spriteSheet, render, mngr) { }

Block::~Block() { }

void Block::handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> /*collidingObjects*/) { }

void Block::update(float const& /*deltaTime*/) { }

void Block::willCollide(std::vector<GameObject*> const& /*objects*/) { }