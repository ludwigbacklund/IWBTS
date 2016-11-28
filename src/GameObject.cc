#include "GameObject.h"
#include <SDL2/SDL.h>
#include <array>
#include <iostream>
#include <SDL2/SDL_image.h>	

/**
 * @brief Constructor for GameObject
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
GameObject::GameObject(int x_p, int y_p, int w, int h, int amountOfFrames, std::string spriteSheet, SDL_Renderer* render, TextureManager* mngr)
: xPos{x_p}, yPos{y_p}
{
    sprite = new Sprite(xPos, yPos, w, h, amountOfFrames, spriteSheet, render, mngr);
	sprite -> spriteRect.x = xPos;
	sprite -> spriteRect.y = yPos;
    xPos = 0;
    yPos = 0;
}

GameObject::~GameObject()
{
    delete sprite;
}

/**
 * @brief Updates position
 *
 * Updates the objects position by adding its velocity to its current x and y position values
 */
void GameObject::updatePosition()
{
    sprite -> spriteRect.x = sprite -> spriteRect.x + xVel;
    sprite -> spriteRect.y = sprite -> spriteRect.y + yVel;
}


void GameObject::createObject(std::vector<GameObject*>& /*map_objects*/) { }

/**
 * @brief Kills the object
 *
 * Kills the object by specifying that it should die on the next update
 */
void GameObject::kill()
{
    dieNextUpdate = true;
}

/**
 * @brief Changes objects hp or kills it
 *
 * If the objects health is over one then it removes one hp from it. If the objects health is equal or less than one it kills it instead.
 */
void GameObject::takeDmg()
{
    if (health > 1)
    {
        health -= 1;
    }
    else
    {
        kill();
    }
}

/**
 * @brief Updates position based on gravity calculation
 *
 * Simulates gravity by changing the objects y position
 */
void GameObject::updateGravity(float const& /*deltaTime*/)
{
    if (yVel < 1 && yVel > 0)
    {
        airTime += 0.16667;
        yVel = 1;
    }
    else if (yVel < 2)
    {
        airTime += 0.16667;
        yVel += (7 * airTime / pow(9.82, 2));
    }
}

double GameObject::getXVel() const
{
    return xVel;
}

void GameObject::setXVel(int const& new_xvel)
{
    xVel = new_xvel;
}

double GameObject::getYVel() const
{
    return yVel;
}

void GameObject::setYVel(int const& new_yvel)
{
    yVel = new_yvel;
}

bool GameObject::getDying() const
{
    return dieNextUpdate;
}

int GameObject::getDirection() const
{
    return direction;
}

/**
 * @brief Checks for intersection and returns if a collision has occurred.
 *
 * Checks for a collision between the object calling the function and another object.
 * If a collision has occurred then the collision direction is calculated and saved for use later.
 *
 * @return bool stating if collision has occured
 */
bool GameObject::intersect(GameObject* const& a, std::array<std::string, 4> &result)
{
    int aRightSide = a -> sprite -> spriteRect.x + a -> sprite -> spriteRect.w;
    int aBotSide =  a -> sprite -> spriteRect.y + a -> sprite -> spriteRect.h;
    int newRightSide = sprite -> spriteRect.x  + sprite -> spriteRect.w;
    int newBotSide = sprite -> spriteRect.y + sprite -> spriteRect.h + yVel;
    int newTopSide = sprite -> spriteRect.y + yVel;
    int newLeftSide = sprite -> spriteRect.x;

    bool collided = !((a -> sprite -> spriteRect.x > newRightSide || aRightSide < (newLeftSide))
                      || (a -> sprite -> spriteRect.y > (newBotSide) || aBotSide < (newTopSide)));

    if (collided)
    {
        if ((a -> sprite -> spriteRect.y >= newTopSide) && (a -> sprite -> spriteRect.y <= newBotSide))
        {
            result[0] = "top_y";
        }
        else if (aBotSide >= (newTopSide) && sprite -> spriteRect.y >= aBotSide)
        {
            result[1] = "bot_y";
        }
        else if (a -> sprite -> spriteRect.x >= newLeftSide && a -> sprite -> spriteRect.x <= newRightSide)
        {
            result[2] = "left_x";
        }
        else if ((aRightSide >= newLeftSide) && (a -> sprite -> spriteRect.x < (newLeftSide)))
        {
            result[3] = "right_x";
        }
        else
        {
            std::cout << "no collision direction" << std::endl;
        }
    }
    return collided;
}

std::string GameObject::getType() const
{
    return type;
}

int GameObject::getHealth() const
{
    return health;
}

