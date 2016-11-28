#include "SpeedDemon.h"

/**
 * @brief Constructor for SpeedDemon
 *
 * @param xPos x position of object
 * @param yPos y position of object
 * @param player_ptr pointer to extract its coordinates
 * @param render renderer to draw to
 * @param mngr texture manager to use with sprite
 */
SpeedDemon::SpeedDemon(int x_pos, int y_pos, SDL_Renderer* render, Player* player_ptr, TextureManager* mngr)
: Enemy(x_pos, y_pos, 11, 15, 8, "./images/speeddemoncompressed.png", render, player_ptr, mngr)
{
    health = 5;
}

/**
 * @brief Update function for SpeedDemon
 *
 */
void SpeedDemon::update(float const& deltaTime)
{
    collidedThisUpdate = false;
    decideAction();
    updatePosition();
    updateGravity(deltaTime);
}

/**
 * @brief collision handeling for SpeedDemon
 *
 * If collision with a block has occured, depending on direction reset velocity values
 * If collision with a player has occured, activate players takeDmg() function.
 *
 */
void SpeedDemon::handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects)
{
    for (auto object : collidingObjects) {
        std::string obj_type = object.first -> getType();
        if (!collidedThisUpdate && obj_type == "block") {
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
                sprite -> spriteRect.y += -1;
                airTime = 0;
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
 * @brief Collision check for SpeedDemon
 *
 * Iterates the vector with objects in map and sends them to intersect
 *
 */


void SpeedDemon::willCollide(std::vector<GameObject*> const& objects)
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
    return handleCollision(collided_types);
}

/**
 * @brief sets run animation
 *
 */
void SpeedDemon::running()
{
    sprite -> setAnimationStartIndex(4);
    sprite -> setAnimationEndIndex(7);
}

/**
 * @brief sets idle animation
 *
 */
void SpeedDemon::idle()
{
    sprite -> setAnimationEndIndex(3);
    sprite -> setAnimationStartIndex(0);
    sprite -> setAnimationCurrent(0);
}

/**
 * @brief Calculates next action
 *
 * If Player x is to the left of object and difference in y is less than 100, move to the left.
 * If Player x is to the right of object and difference in y is less than 100, move to the right
 * If Player is not within reach or same x, stand still.
 */
void SpeedDemon::decideAction()
{
    if (player -> sprite -> spriteRect.x < sprite -> spriteRect.x &&
        abs(sprite -> spriteRect.y - player -> sprite -> spriteRect.y) < 100)
    {
        running();
        xVel = -1;
        direction = -1;


    }
    else if (player -> sprite -> spriteRect.x > sprite -> spriteRect.x &&
            abs(sprite -> spriteRect.y - player -> sprite -> spriteRect.y) < 100)
    {
        running();
        xVel = 1;
        direction = 1;
    }
    else
    {
        xVel = 0;
        idle();
    };

}