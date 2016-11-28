#include "MrRabbit.h"
#include "MrRabbitProjectile.h"

/**
 * @brief Constructor for MrRabbit
 *
 * @param xPos x position of mr. rabbit
 * @param yPos y position of mr. rabbit
 * @param render renderer to draw to
 * @param player_ptr pointer to active player
 * @param mngr texture manager to use with sprite
 */
MrRabbit::MrRabbit(int x_pos, int y_pos, SDL_Renderer* render, Player* player_ptr,TextureManager* mngr)
        :Enemy(x_pos, y_pos, 13, 24, 2, "./images/mrrabbitcompressed.png", render, player_ptr, mngr)
{
    health = 8;
}

/**
 * @brief Updator for MrRabbit
 *
 * Resets the bool that states if a collision has occurred this update.
 * Decides the next action to take.
 * Updates the time variable used to make decisions and the time since last shot variable.
 * Updates x position of the object.
 * Updates y position of the object according to gravity calculations.
 */
void MrRabbit::update(float const& deltaTime)
{
    collidedThisUpdate = false;
    decideAction();
    updateTime += 1 * deltaTime;
    timeSinceShot += 1 * deltaTime;
    updatePosition();
    updateGravity(deltaTime);
}

/**
 * @brief Collision handler for MrRabbit
 *
 * Handles collision with blocks by stopping it at appropriate times.
 * Handles collision with player by incurring damage on player.
 */
void MrRabbit::handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects)
{
    for (auto object : collidingObjects) {
        std::string obj_type = object.first -> getType();

        if (obj_type == "block" && collidedThisUpdate == false) {
            collidedThisUpdate = true;
            if (object.second[2] == "left_x") {
                setXVel(0);
                sprite -> spriteRect.x += -1;
            }
            if (object.second[3] == "right_x") {
                sprite -> spriteRect.x += 1;
                setXVel(0);
            }
            if (object.second[1] == "bot_y") {
                sprite -> spriteRect.y += 1;
                yVel = 0;
            }
            if (object.second[0] == "top_y") {
                airTime = 0;
                sprite -> spriteRect.y += -1;
                setYVel(0);
            }
        }
        if (obj_type == "player")
        {
            object.first -> takeDmg();
        }
    }
}

/**
 * @brief Creates the mr. rabbit projectile
 *
 * Creates mr. rabbits projectile if he is able to shoot and then resets the variable related to shooting
 */
void MrRabbit::createObject(std::vector<GameObject*> &map_objects)
{
    if (shootNextUpdate && timeSinceShot >= 1)
    {
    map_objects.push_back(new MrRabbitProjectile{sprite -> spriteRect.x + sprite -> spriteRect.w / 2,
                                                 sprite -> spriteRect.y + 10, getDirection(),
                                                 sprite -> getRenderer(),
                                                 this,
                                                 sprite -> textureManager
    });
    timeSinceShot = 0;
    shootNextUpdate = false;
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
void MrRabbit::willCollide(std::vector<GameObject*> const& objects)
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
 * @brief Decides the next action for mr. rabbit
 *
 * Shoots next update and changes to correct direction if player is within a certain x or y distance.
 * Moves right or left depending in the time since last movement.
 */
void MrRabbit::decideAction()
{
    if (player -> sprite -> spriteRect.x < sprite -> spriteRect.x &&
        abs(sprite -> spriteRect.y - player -> sprite -> spriteRect.y) < 40)
    {
        shootNextUpdate = true;
        direction = -1;
    }
    else if (player -> sprite -> spriteRect.x > sprite -> spriteRect.x &&
             abs(sprite -> spriteRect.y - player -> sprite -> spriteRect.y) < 40)
    {
        shootNextUpdate = true;
        direction = 1;
    }
    else
    {
        if (updateTime >= 1)
        {
            updateTime = 0;
        }
        if (updateTime > 0.5)
        {
            moveLeft();
        }
        else if (updateTime < 0.5)
        {
            moveRight();
        }
    }
}