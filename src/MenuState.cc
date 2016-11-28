#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include "Button.h"
#include "MenuState.h"

/**
 * @brief Constructor for MenuState
 *
 * @param win window to draw to
 * @param rend renderer to draw to
 */
MenuState::MenuState(SDL_Window* win, SDL_Renderer* rend)
{
    window = win;
    renderer= rend;

    init();
}

/**
 * @brief Cleanup for MenuState
 *
 * Deletes all buttons and the background.
 */
MenuState::~MenuState()
{
    for (Button* object : menuItems)
    {
        delete object;
    }
    menuItems.clear();
    delete background;
}

/**
 * @brief Destructor for MenuState
 *
 * Loads image to menu background and adds buttons for the different levels.
 */
void MenuState::init()
{
    background = new Sprite{0, 0, 800, 600, 1, "./images/menubackground.png", renderer, mngr};

    menuItems.push_back(new Button(305, 120, 190, 75, renderer, "./images/level1.png", "./levels/Level1.lvl", 1, mngr));
    menuItems.push_back(new Button(305, 200, 190, 75, renderer, "./images/level2.png", "./levels/Level1Boss.lvl", 1, mngr));
}

/**
 * @brief Updator for MenuState
 *
 * Clears the screen and draws the background and buttons.
 */
void MenuState::update(float const& /*deltaTime*/)
{
    SDL_RenderClear(renderer);
    background -> draw(1);
    for(Button* button : menuItems )
    {
        button -> sprite -> draw(1);
    }
    SDL_RenderPresent(renderer);
}

/**
 * @brief Event handler for MenuState
 *
 * Handles mouse clicks and checks if the click occurred on a button and then loads the appropriate level.
 */
void MenuState::handle(SDL_Event event, float /*deltaTime*/)
{
    int x{0};
    int y{0};
    SDL_GetMouseState(&x, &y);
    if(event.type == SDL_MOUSEBUTTONDOWN) {
        for (Button *button : menuItems) {
            if (button -> checkForClick(x, y)) {
                nextState = button -> clickStatechange;
                level = button -> clickValue;
                pause = true;
            }
        }
    }
}