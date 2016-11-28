#include "GameObject.h"
#include "PlayState.h"
#include "Player.h"
#include "Block.h"
#include "Border.h"
#include "Projectile.h"
#include "Enemy.h"
#include "SpeedDemon.h"
#include "MrRabbit.h"
#include "Checkpoint.h"
#include "GrassBlock.h"
#include "SpikeBlock.h"
#include "TriggerBlock.h"
#include "FallBlock.h"
#include "JumpBlock.h"
#include "Skeletron.h"
#include "FinishBlock.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * @brief Constructor for PlayState
 *
 * @param win window to draw to
 * @param rend renderer to draw to
 */
PlayState::PlayState(SDL_Window* win, SDL_Renderer* rend)
{
    window = win;
    renderer= rend;
}

/**
 * @brief Destructor for PlayState
 *
 * Deletes every object in the game objects vector and the background.
 */
PlayState::~PlayState()
{
    for (GameObject* object : objects)
    {
        delete object;
    }
    delete mngr;
    delete background;
    objects.clear();
}

/**
 * @brief Inititalizer for PlayState
 *
 * Loads and draws the background image for the play state.
 * Loads the chosen level.
 */
void PlayState::init()
{
    background = new Sprite{0, 0,800,600,1, "./images/Background.png", renderer, mngr};
    loadLevel(level);
}

/**
 * @brief Loads the objects from a .lvl file to the game field by calling createObject for every valid line
 *
 * Clears the map objects vector and reserves enough space to hold all objects.
 * Outputs a status message to the console.
 * Initializes variables needed to create objects.
 * Opens the level file.
 * Uses stringstreams to load each line into the preivously created variables.
 * Sends the variables to createObject() if the object is valid.
 * Creates borders around the game screen.
 */
void PlayState::loadLevel(std::string level){
    objects.clear();
    objects.reserve(64);

    std:: cout << "Loading level " << level << std::endl;
    std::string line;
    std::string obj_name;

    int obj_x;
    int obj_y;
    int extra;
    std::string path;
    bool valid{true};
    int lineNumber = 0;
    std::ifstream level_file(level);

    while (std::getline(level_file,line))
    {
        lineNumber += 1;
        std::istringstream iss(line);
        if (!(iss >> obj_name))
        {
            std::cerr << "invalid object name at line " << lineNumber<< std::endl;
            valid = false;
        }
        if (!(iss >> obj_x))
        {
            std::cerr << "invalid object x value at line " << lineNumber<< std::endl;
            valid = false;
        }

        if(!(iss >> obj_y))
        {
            std::cerr << "invalid object y value at line " << lineNumber << std::endl;
            valid = false;
        }
        if(!(iss >> extra)  )
        {
            iss.clear();
            iss >> path;

        }
        if (valid == true)
        {
            createObject(obj_name, obj_x, obj_y, extra, path, renderer);
        }
    }

    objects.push_back(new Border(0,-10,800,10, renderer, mngr));
    objects.push_back(new Border(0,0,4,600, renderer, mngr));
    objects.push_back(new Border(798,0,10,600, renderer, mngr));
    objects.push_back(new Border(0,598,800, 10, renderer, mngr));
}

/**
 * @brief Creates an object on the game screen
 *
 * Creates the appropriate object depending on the name specified and pushes it to the game object vector.
 */
void PlayState::createObject(std::string name, int x, int y, int extra, std::string path, SDL_Renderer* renderer)
{
    if (name == "player")
    {
        if (playerX != 0 && playerY != 0)
        {
            x = playerX;
            y = playerY;
        }
        Player* player = new Player(x,y, renderer, mngr);
        objects.push_back(player);
    }
    else if (name == "block")
    {
        objects.push_back(new GrassBlock(x, y, renderer, mngr));

    }
    else if (name == "FinishBlock")
    {
        objects.push_back(new FinishBlock(x, y, renderer, static_cast<bool>(extra), mngr));


    }
    else if (name == "SpeedDemon")
    {
        objects.push_back(new SpeedDemon(x, y, renderer, dynamic_cast<Player*>(objects.at(0)), mngr));
    }
    else if (name == "MrRabbit")
    {
        objects.push_back(new MrRabbit(x, y, renderer, dynamic_cast<Player*>(objects.at(0)), mngr));
    }
    else if (name == "Checkpoint")
    {
        objects.push_back(new Checkpoint(x, y, renderer, mngr));
    }
    else if (name == "SpikeBlock")
    {
        objects.push_back(new SpikeBlock(x, y, renderer, extra, mngr));

    }
    else if (name == "TriggerBlock")
    {
        ActiveBlock* targetObject = dynamic_cast<ActiveBlock*>(objects.at(extra-1));
        if (targetObject != nullptr)
        {
            objects.push_back(new TriggerBlock(x, y, renderer,targetObject, mngr));
        }
        else
        {
            std::cerr << "Invalid block for trigger" << std::endl;
        }

    }
    else if (name == "FallBlock")
    {
        objects.push_back(new FallBlock(x, y, renderer, static_cast<bool>(extra), mngr));
    }
    else if (name == "JumpBlock")
    {
        objects.push_back(new JumpBlock(x, y, renderer, mngr));
    }
    else if (name == "Continuator")
    {
        objects.push_back(new Continuator(x, y, renderer,path, mngr));
    }
    else if (name == "Skeletron")
    {
        ActiveBlock* onDeath = dynamic_cast<ActiveBlock*>(objects.at(extra-1));
        if (onDeath != nullptr)
        {
            objects.push_back(new Skeletron(x, y, renderer,dynamic_cast<Player*>(objects.at(0)),onDeath, mngr));
        }
    }
    else
    {
        std::cerr << name << "is not an valid object"<< std::endl;
    }
}

/**
 * @brief Event handler for PlayState
 *
 * Fetches a pointer to the player from the game objects vector.
 * Moves to menu state if escape is pressed.
 * Moves player to new sublevel if applicable.
 * Sends events to player event handler.
 */
void PlayState::handle(SDL_Event event, float deltaTime)
{
    GameObject* nplayer = objects.at(0);
    Player* player = dynamic_cast<Player*>(nplayer);
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym ==  SDLK_ESCAPE)
        {
            playerX = player ->xPos;
            playerY = player ->yPos;
            nextState = 0;
            pause= true;
        }
    }

    if (player->shouldChangeSubLevel())
    {
        int tempX = player ->xPos;
        int tempY = player ->yPos;
        playerX = 0;
        playerY = 0;
        loadLevel(player -> getNextSubLevel());
        level = player -> getNextSubLevel();
        playerX = tempX;
        playerY = tempY;
    }

    player -> handle(event, deltaTime);
}

/**
 * @brief Updater for PlayState
 *
 * Clears the screen.
 * Draws the background.
 * Loops through every object on the game screen.
 * If an object is moving, check for collision with it and every other object.
 * Create projectiles for object if applicable.
 * Update object.
 * Draw object in the correct direction.
 * Move to deathstate if player dies.
 * Move to menustate if player finishes game.
 * Delete object.
 */
void PlayState::update(float const& deltaTime)
{
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    background -> draw(1);
    for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); /*++it*/)
    {
        if ((*it) -> getXVel() != 0 || (*it) -> getYVel() != 0)
        {
            (*it) -> willCollide(objects);
        }
        (*it) -> createObject(objects);
        (*it) -> update(deltaTime);
        (*it) -> sprite -> draw((*it) -> getDirection());
        if ((*it) -> getDying() == true)
        {
            if ((*it) -> getType() == "player")
            {
                playerX = (*it) ->xPos;
                playerY = (*it) ->yPos;
                nextState = 2;
                pause = true;
                break;
            }
            if ((*it) -> getType() == "finish")
            {
                nextState = 0;
                pause = true;
                break;
            }
            delete *it;
            it = objects.erase(it);
        }
        else
        {
            ++it;
        }
    }

    SDL_RenderPresent(renderer);
}