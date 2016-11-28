#include "Button.h"

/**
 * @brief Constructor for Button class
 *
 * @param x x position of button
 * @param y y position of button
 * @param w width of button
 * @param h height of button
 * @param render renderer to draw to
 * @param buttonImage location of image to draw to button
 * @param newLevelName name of level to load on click
 * @param newStateIndex index of state to change to
 * @param mngr texture manager to use with sprite
 */
Button::Button(int x, int y, int w, int h, SDL_Renderer* render, std::string buttonImage, std::string newLevelName, int newStateIndex, TextureManager* mngr)
        : clickStatechange{newStateIndex}, clickValue{newLevelName}
{
    sprite = new Sprite(x, y, w, h, 1, buttonImage, render,mngr);
}
/**
 * @brief destructor for Button class
 *
 * Deletes sprite pointer
 */
Button::~Button()
{
    delete sprite;
}

/**
 * @brief Checks for click on button
 *
 * Compares x and y position of click with x and y position of button to see if the click occured on the button
 *
 * @param x x position of click
 * @param y y position of click
 */
bool Button::checkForClick(int x, int y)
{
    return x >= sprite -> spriteRect.x && x <= sprite -> spriteRect.x + sprite -> spriteRect.w
           && y >= sprite -> spriteRect.y && y <= sprite -> spriteRect.y + sprite -> spriteRect.h;
}