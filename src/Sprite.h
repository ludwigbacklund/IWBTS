#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include "TextureManager.h"

class Sprite
{
public:
    Sprite(int x_p, int y_p,int w, int h, int amountOfFrames,std::string spriteSheet, SDL_Renderer* render, TextureManager* mngr);
    ~Sprite();

    void draw(int const& direction);
    void updateAnimation();
    void loadSprite();

    void setAnimationCurrent(int const& newAnimationFrame);
    void setAnimationProgress(int const& newAnimationFrame);
    void setAnimationStartIndex(int const& newAnimationFrame);
    void setAnimationEndIndex(int const& newAnimationFrame);

    int getAnimationCurrent() const;
    int getAnimationProgress() const;
    int getAnimationStartIndex() const;
    int getAnimationEndIndex() const;
    SDL_Renderer* getRenderer() const;

    TextureManager* textureManager;
    SDL_Texture* texture;
    SDL_Rect spriteClips[8];
    SDL_Rect spriteRect;

private:
    SDL_Renderer* renderer;
    std::string sheetPath{""};
    int frameAmount{1};
    int animationCurrent{0};
    int animationProgress{0};
    int animationStartIndex{0};
    int animationEndIndex{0};
};

#endif