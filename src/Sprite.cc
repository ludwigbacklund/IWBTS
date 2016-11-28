#include "Sprite.h"
#include <array>
#include <iostream>

/**
 * @brief Constructor for Sprite
 *
 * @param x_p x position of object
 * @param y_p y position of object
 * @param w width of each animation frame
 * @param h height of each animation frame
 * @param amountOfFrames amount of frames in blocks spritesheet
 * @param spriteSheet location of spritesheet
 * @param render renderer to draw to
 * @param mngr texture manager to use with sprite
 */
Sprite::Sprite(int x_p, int y_p,int w, int h, int amountOfFrames, std::string spriteSheet, SDL_Renderer* render, TextureManager* mngr)
: renderer{render}, sheetPath{spriteSheet}, frameAmount{amountOfFrames}, textureManager{mngr}
{
    animationCurrent = 0;
    spriteRect.x = x_p;
    spriteRect.y = y_p;
    spriteRect.w = w;
    spriteRect.h = h;
    if ((getAnimationStartIndex() == 0 && getAnimationEndIndex() == 0) && frameAmount > 1 )
    {
        setAnimationEndIndex(frameAmount-1);
    }
    loadSprite();
}

Sprite::~Sprite() { }

/**
 * @brief Draws the current object
 *
 * Depending on the objects direction, draws a flipped image
 */
void Sprite::draw( int const& direction)
{
    updateAnimation();
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

    if (direction >= 0)
    {
        SDL_RenderCopy(renderer,texture, &spriteClips[animationCurrent],  &spriteRect);
    }
    else
    {
        SDL_RenderCopyEx(renderer, texture, &spriteClips[animationCurrent], &spriteRect, 0, nullptr, flip);
    }
}

/**
 * @brief Updates the animation
 *
 * Depending on the current animation and how many animation it contains, it resets the animation value
 * animationCurrent is used to specifiy which parts of the spritesheet to display
 */
void Sprite::updateAnimation()
{
    if (getAnimationCurrent() < getAnimationStartIndex() || getAnimationCurrent() > getAnimationEndIndex())
    {
        setAnimationCurrent(getAnimationStartIndex());
    }

    if (getAnimationProgress() == 10 )
    {
        animationProgress = 0;
        if (animationCurrent < animationEndIndex)
        {
            animationCurrent += 1;
        }
        else
        {
            animationCurrent = animationStartIndex;
        }
    }
    else
    {
        animationProgress += 1;
    }
}

void Sprite::setAnimationCurrent(int const& newAnimationFrame) { animationCurrent = newAnimationFrame; }

void Sprite::setAnimationProgress(int const& newAnimationFrame) { animationProgress = newAnimationFrame; }

void Sprite::setAnimationStartIndex(int const& newAnimationFrame) { animationStartIndex = newAnimationFrame; }

void Sprite::setAnimationEndIndex(int const& newAnimationFrame) { animationEndIndex = newAnimationFrame; }

int Sprite::getAnimationProgress() const { return animationProgress; }

int Sprite::getAnimationEndIndex() const { return animationEndIndex; }

int Sprite::getAnimationStartIndex() const { return animationStartIndex; }

int Sprite::getAnimationCurrent() const { return animationCurrent; }

SDL_Renderer* Sprite::getRenderer() const { return renderer; }

/**
 * @brief Loads the sprite from given path
 *
 * Converts the image to and Texture* via Surface*
 * Creates spriteclips depending on size and height of spriteRect
 *
 */
void Sprite::loadSprite()
{
    texture = textureManager -> getTexture(sheetPath,renderer);
    int i{0};
    while (i != frameAmount)
    {
        spriteClips[i].x = 0 + ( i * (spriteRect.w +1));
        spriteClips[i].y = 0;
        spriteClips[i].w = spriteRect.w;
        spriteClips[i].h = spriteRect.h;
        i += 1;
    }
}