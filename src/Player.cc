#include "Player.h"
#include "Block.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <utility>
#include <math.h>
#include <array>

/**
 * @brief Constructor for Player
 *
 * @param xPos x position of player
 * @param yPos y position of player
 * @param render renderer to draw to
 */
Player::Player(int x_pos, int y_pos, SDL_Renderer* render, TextureManager* mngr)
: GameObject(x_pos, y_pos, 11, 15, 8, "./images/akicompressed.png", render, mngr)
{
    setIdleAnimation();
    type = "player";
}

Player::~Player() { }

/**
 * @brief Moves the player to the left next update by changing its x velocity now
 */
void Player::moveLeft()
{
     if (getXVel() > -2)
    {
        setXVel(-2);
    }
}

/**
 * @brief Moves the player to the right next update by changing its x velocity now
 */
void Player::moveRight()
{
     if (xVel < 2)
    {
        xVel = 2;
    }
}

/**
 * @brief Makes player jump
 *
 * Changes y velocity of player to make it jump.
 * Removes one from its jumpPower to make sure player cant doublejump.
 */
void Player::jump(float const& /*deltaTime*/)
{
    if (jumpPower > 0)
    {
        if (getYVel() > -1)
        {
            setYVel(-1);
        }
        if (getYVel() > -2)
        {
            setYVel(getYVel() - 2);
        }
        jumpPower -= 1;
    }
}

/**
 * @brief Shoots projectile
 *
 * Shoots a projectile next update if enough time has passed since last shot
 */
void Player::shoot()
{
    if (timeSinceShot >= 0.25)
    {
        shootNextUpdate = true;
    }
}

/**
 * @brief Event handler for Player
 *
 * Resets x velocity to zero when movement keys are no longer pressed.
 * Resets boolean that states if projectile can be shot next update when spacebar is no longer pressed.
 * Calls appropriate move or jump functions if movement keys are presesed.
 * Calls shoot function if space bar is pressed.
 * Kills player if R is pressed.
 */
void Player::handle(SDL_Event event, float deltaTime)
{
	if(event.type == SDL_KEYUP)
    {
		if(event.key.keysym.sym ==  SDLK_d)
		{
            if (getXVel() > 0)
            {
               setXVel(0);
            }
            setIdleAnimation();
		}
		if(event.key.keysym.sym == SDLK_a)
		{
            if (getXVel() < 0)
            {
                setXVel(0);
            }
            setIdleAnimation();
		}
        if(event.key.keysym.sym == SDLK_SPACE)
        {
            canShoot = true;
        }
	}
	if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym ==  SDLK_d)
			{
                moveRight();
                setRunningAnimation();
                direction = 1;
			}

			else if(event.key.keysym.sym == SDLK_a)
			{
                moveLeft();
                setRunningAnimation();
                direction = -1;
			}

			if(event.key.keysym.sym == SDLK_w)
            {
                jump(deltaTime);
			}
            if(event.key.keysym.sym == SDLK_SPACE)
            {
                shoot();
            }
            if(event.key.keysym.sym == SDLK_r)
            {
                kill();
            }
		}
}

/**
 * @brief Sets the current animation indexes to correspond with the running frames
 */
void Player::setRunningAnimation()
{
	sprite -> setAnimationStartIndex(4);
	sprite -> setAnimationEndIndex(7);
    sprite -> setAnimationCurrent(4);
}

/**
 * @brief Sets the current animation indexes to correspond with the setIdleAnimation frames
 */
void Player::setIdleAnimation()
{
	sprite -> setAnimationEndIndex(3);
	sprite -> setAnimationStartIndex(0);
	sprite -> setAnimationCurrent(0);
}

/**
 * @brief Collision handler for Player
 *
 * Loops through all colliding objects.
 * Gets type of colliding object.
 * Dies if object is a spike block.
 * If object is a checkpoint it sets players respawn x and y position to the position of the checkpoint.
 * If object is a fall block it activates the fall block.
 * If object is a continuator and the player won't die next update it sets the players respawn x and y position to that which the continuator points to and changes the next sublevel to the continuators sublevel.
 * If object is a trigger block it activates it.
 * If object is a jump block it adds one to its jump power, resets its airtime and kills the jump block.
 * If object is a finish block it kills it.
 * If player hasn't collided with a block or a border this update it handles a collision with them appropriately by changing the players and x and y position to not be intersecting.
 * Kills player if collision with a border located on the bottom of the screen (falling).
 */
void Player::handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects)
{
    for(auto object : collidingObjects)
    {
        std::string obj_type = object.first -> getType();
        if (obj_type == "spikeblock")
        {
           kill();
        }
        if (obj_type == "checkpoint")
        {
            xPos = object.first -> sprite -> spriteRect.x;
            yPos = object.first -> sprite -> spriteRect.y;
        }
        if (obj_type == "fallblock")
        {
            ActiveBlock* fallblock = dynamic_cast<ActiveBlock*>(object.first);
            fallblock -> activate();
        }
        if (obj_type == "continuator" && !dieNextUpdate)
        {
            Continuator* gate = dynamic_cast<Continuator*>(object.first);
            xPos = object.first -> sprite -> spriteRect.x;
            yPos = object.first -> sprite -> spriteRect.y;
            nextSubLevel = gate -> getSubLevelPath();
        }
        if (obj_type == "triggerblock")
        {
            ActiveBlock* trigger = dynamic_cast<ActiveBlock*>(object.first);
            trigger -> activate();
        }
        if (obj_type == "jumpblock")
        {
            jumpPower += 1;
            airTime = 0;
            object.first -> kill();
        }
        if (obj_type == "finish")
        {
            object.first -> kill();
        }
        if (!collidedThisUpdate && (obj_type == "block" || obj_type == "border"))
        {
            collidedThisUpdate = true;
            if (object.second[2] == "left_x")
            {
                sprite -> spriteRect.x += -1;
                setXVel(0);
            }
            if (object.second[3] == "right_x")
            {
                sprite -> spriteRect.x += 1;
                setXVel(0);
            }
            if (object.second[1] == "bot_y")
            {
                sprite -> spriteRect.y += 1;
                setYVel(0);
            }
            if (object.second[0] == "top_y")
            {
                sprite -> spriteRect.y += -1;
                airTime = 0;
                if (obj_type != "border")
                {
                    setYVel(0);
                    jumpPower = 1;
                }
                else
                {
                    kill();
                }
            }
        }
    }
}

/**
 * @brief Checks for collision with every object on the screen and handles it if collision has occurred.
 *
 * Creates a vector that will contain the object and the type of the object it collides with.
 * Creates a vector with the resulting collision direction of the object it collides with.
 * Loops through all objects on screen and checks for collision.
 * Calls handleCollision() with the previously mentioned vector containing the object and its type.
 */
void Player::willCollide(std::vector<GameObject*> const& objects)
{
    std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collided_types;
    std::array<std::string, 4> result;
    for (GameObject* object : objects)
    {
        if (object != this && intersect(object, result))
        {
            collided_types.push_back(std::make_pair(object, result));
        }
    }
    handleCollision(collided_types);
}

/**
 * @brief Updator for Player
 *
 * Resets the bool that states if a collision has occurred this update.
 * Updates the time since last shot.
 * Updates x position of the object.
 * Updates y position of the object according to gravity calculations.
 */
void Player::update(float const& deltaTime)
{
    collidedThisUpdate = false;
    if (timeSinceShot < 0.25)
    {
        timeSinceShot += 1 * deltaTime;
    }
    updatePosition();
    updateGravity(deltaTime);
}

/**
 * @brief Creates the players projectile
 *
 * Creates player projectile if he is able to shoot and then resets the variable related to shooting
 */
void Player::createObject(std::vector<GameObject*> &map_objects)
{
    if (shootNextUpdate == true && canShoot == true)
    {
        map_objects.push_back(new PlayerProjectile{sprite -> spriteRect.x + sprite -> spriteRect.w / 2,
                                             sprite -> spriteRect.y, getDirection(),
                                             sprite -> getRenderer(),
                                             this,
                                               sprite -> textureManager
        });
        timeSinceShot = 0;
        shootNextUpdate = false;
        canShoot = false;
    }
}

/**
 * @brief Determines if it should (can) change sublevel
 *
 * @return if the next sublevel isn't an empty string it returns true.
 */
bool Player::shouldChangeSubLevel()
{
    if (nextSubLevel != "")
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Player::getNextSubLevel() {
    return nextSubLevel;
}
