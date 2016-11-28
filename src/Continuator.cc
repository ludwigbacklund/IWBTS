#include "Continuator.h"

/**
 * @brief Constructor for Continuator class
 *
 * @param x x position of continuator
 * @param y y position of continuator
 * @param renderer renderer to draw to
 * @param path location of new level to change to
 * @param mngr texture manager to use with sprite
 */
Continuator::Continuator(int x, int y, SDL_Renderer* renderer, std::string path, TextureManager* mngr)
        : ActiveBlock(x, y, 16, 32, 4, "./images/teleportercompressed.png", renderer, mngr), subLevelPath{path}
{
    sprite -> setAnimationStartIndex(0);
    sprite -> setAnimationEndIndex(3);
    type = "continuator";
}

void Continuator::activate() { }

std::string Continuator::getSubLevelPath()
{
    return subLevelPath;
}