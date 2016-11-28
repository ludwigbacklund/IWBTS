#ifndef BUTTON_H
#define BUTTON_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <utility>
#include "GameObject.h"

class Button
{
public:
    Button(int x, int y, int w, int h, SDL_Renderer* render, std::string buttonImage, std::string newLevelName, int newStateIndex, TextureManager* mngr);
    ~Button();

    bool checkForClick(int x, int y);

    Sprite* sprite;
    int clickStatechange;
    std::string clickValue;
};
#endif