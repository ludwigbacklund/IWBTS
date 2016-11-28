#include "StateMachine.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

/**
 * @brief Initializer for StateMachine
 *
 * Creates windows with SCREEN_WIDTH and SCREEN_HEIGHT
 * Creates a renderer to use for drawing
 * Creates the different gamestates and adds them to a vector
 * Changes the current state to display the menu
 * Calls update for the current state
 */
void StateMachine::init()
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO /*|SDL_INIT_AUDIO*/) != 0) {
        std::cerr << "Error initializing SDL" << std::endl;
        exit(1);
    }
    // create the window
    window = SDL_CreateWindow("I wanna be the Scrub", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
    // make the scaled rendering look smoother
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    // render at a virtual resolution then stretch to actual resolution
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    play = new PlayState(window, renderer);
    menu = new MenuState(window,renderer);
    endmenu = new DeathState(window,renderer);
    states.push_back(menu);
    states.push_back(play);
    states.push_back(endmenu);
    changeState(menu);
    update();
}

/**
 * @brief Destructor for StateMachine
 *
 * Deallocates the different gamestates
 * Deletes the Window
 * Deletes the renderer
 */
StateMachine::~StateMachine()
{
    for( GameState* state : states)
    {
        delete state;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

/**
 * @brief State changer StateMachine
 *
 * Switches the member variable currentState to the gamestate pointer
 * Initializes the new gamestate
 */
void StateMachine::changeState(GameState* newState)
{
    currentState = newState;
    newState -> init();
}

/**
 * @brief Transfers values between new and old gamestate
 *
 * Used for saving which level the playstate should load
 * Saves the players coordinates, used for respawning at a checkpoint
 */
void StateMachine::TransferStateValues(GameState* NextCurrentState)
{
    if (NextCurrentState -> level == currentState -> level || NextCurrentState == states.at(2))
    {
        NextCurrentState -> playerX = currentState -> playerX;
        NextCurrentState -> playerY = currentState -> playerY;
    }
    else
    {
        NextCurrentState -> playerX = 0;
        NextCurrentState -> playerY = 0;
    }
    NextCurrentState -> level = currentState -> level;
}

/**
 * @brief Calls current gamestates update function
 *
 * Calculates the time between frames
 * Calls update function in the current gamestate with deltaTime as parameter
 */
void StateMachine::update()
{

    bool running{true};

    const Uint32 targetFrameDelay = 10;
    Uint32 startTime = SDL_GetTicks();
    Uint32 lastFrameTime = startTime;

    while(running)
    {
        if (currentState -> pause)
        {
            GameState* NextCurrentState = states.at(currentState -> nextState);
            TransferStateValues(NextCurrentState);
            currentState -> pause = false;
            changeState(NextCurrentState);
        }

        Uint32 frameDelay = SDL_GetTicks() - lastFrameTime;
        float deltaTime = frameDelay / 1000.0f;
        lastFrameTime += frameDelay;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else
            {
                currentState -> handle(event, deltaTime);
            }
        }

        currentState -> update(deltaTime);

        frameDelay = SDL_GetTicks() - lastFrameTime;
        if (targetFrameDelay > frameDelay)
        {
            Uint32 sleepTime = targetFrameDelay - frameDelay;
            SDL_Delay(sleepTime);
        }

    }
}

GameState* StateMachine::getCurrentState()
{
    return currentState;
}

