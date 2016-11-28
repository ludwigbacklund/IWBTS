#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include "Button.h"
#include "DeathState.h"

/**
 * @brief Constructor for DeathState
 *
 * @param win window to draw to
 * @param rend renderer to draw to
 */
DeathState::DeathState(SDL_Window* win, SDL_Renderer* rend)
{
    window = win;
    renderer = rend;
}

/**
 * @brief Destructor for DeathState
 *
 * Deletes the background pointer
 */
DeathState::~DeathState()
{
    delete background;
}

/**
 * @brief Initiator for Deathstate
 *
 * Loads image to screen on death
 */
void DeathState::init()
{
    background = new Sprite{0, 0,800,600,1,"./images/udiedalpha.png", renderer, mngr};

}

/**
 * @brief Updator for DeathState
 *
 * Clears screen, draws the background, draws the buttons and renders it all on update
 */
void DeathState::update(float const& /*deltaTime*/)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    background -> draw(1);
    SDL_RenderPresent(renderer);
}

/**
 * @brief Event handler for DeathState
 *
 * Switches to play state if spacebar is pressed
 *
 * @param event event to handle
 */
void DeathState::handle(SDL_Event event, float /*deltaTime*/) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_SPACE) {
            nextState = 1;
            pause = true;
        }
    }
}
