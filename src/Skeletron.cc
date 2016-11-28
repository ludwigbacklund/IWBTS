#include "Skeletron.h"
#include "SkeletronProjectile.h"

/**
 * @brief Constructor for Skeletron
 *
 * @param xPos x position of mr. rabbit
 * @param yPos y position of mr. rabbit
 * @param render renderer to draw to
 * @param player_ptr pointer to active player
 * @param target_obj object to activate on death
 * @param mngr texture manager to use with sprite
 */
Skeletron::Skeletron(int x_pos, int y_pos, SDL_Renderer* render, Player* player_ptr, ActiveBlock* target_obj, TextureManager* mngr)
        :Enemy(x_pos, y_pos, 30, 64, 1, "./images/skeletron.png", render, player_ptr, mngr), dropOnDeath{target_obj},
         healthbar{new Sprite(120, 550, 800, 15, 1, "./images/hpbarred.png", render, mngr)}
{
    health = 100;
    tpIndicator = new Sprite(0, sprite-> spriteRect.y + 14, 30, 10, 7, "./images/tpindicatorcompressed.png", render, mngr);
    healthbar -> loadSprite();
    tpIndicator -> loadSprite();
}

/**
 * @brief Deconstructor for Skeletron
 *
 * Deletes the pointer data members.
 */
Skeletron::~Skeletron()
{
    delete healthbar;
    delete tpIndicator;
}

/**
 * @brief Updator for Skeletron
 *
 * Calculates and draws the health bar.
 * Activates target object if dying.
 * Draws the teleport indicator if a teleport is imminent and adds time to the time until teleport.
 * Teleports if its time to teleport.
 * Decides action.
 * Updates x position.
 * Updates y position.
 */
void Skeletron::update(float const& deltaTime)
{
    healthbar -> spriteRect.w = (6  * getHealth());
    healthbar -> draw(1);
    if (dieNextUpdate == true)
    {
        dropOnDeath -> activate();
    }
    if (willTp)
    {
        tpIndicator -> updateAnimation();
        tpIndicator -> draw(1);
        timeToTP += 1 * deltaTime;
    }
    if (timeToTP >= 1)
    {
        timeToTP = 0;
        sprite -> spriteRect.x = tpIndicator -> spriteRect.x;
        willTp = false;
    }
    timeSinceShot += 1*deltaTime;
    decideAction();

    updatePosition();
    updateGravity(deltaTime);
}

/**
 * @brief Collision handler for Skeletron
 *
 * Loops through all colliding objects.
 * Gets type of object.
 * If object is a block it handles the stopping correctly depending on collision direction.
 * If object is a player it incurs damage on the player.
 */
void Skeletron::handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects)
{

    for (auto object : collidingObjects) {
        std::string obj_type = object.first -> getType();
        if (obj_type == "block") {
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
                setYVel(0);
                airTime = 0;
            }
        }
        if (obj_type == "player")
        {
            object.first -> takeDmg();
        }
    }
}

/**
 * @brief Projectile creation for Skeletron
 *
 * Creates skeletrons projectile if he is able to shoot and then resets the variable related to shooting.
 */
void Skeletron::createObject(std::vector<GameObject*> &map_objects)
{
    if (shootNextUpdate && timeSinceShot >= 1.5)
    {
        map_objects.push_back(new SkeletronProjectile{sprite -> spriteRect.x + sprite -> spriteRect.w / 2,
                                                     sprite -> spriteRect.y, getDirection(), directionY,
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
void Skeletron::willCollide(std::vector<GameObject*> const& objects)
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
 * @brief Decision making for Skeletron
 *
 * If the player is nearby or a 1 in 200 chance occurs it will initialize a teleport.
 * Changes direction depending on the players position.
 * Determines where to shoot the projectile depending on the players y position.
 */
void Skeletron::decideAction()
{
    int playerX = player -> sprite -> spriteRect.x;
    int playerY = player -> sprite -> spriteRect.y;
    if (((abs(playerX - sprite -> spriteRect.x ) < 150) || action(rnd) == 10) && !willTp)
    {
        tpIndicator -> spriteRect.x = tp(rnd);
        willTp = true;
    }
    if (playerX < sprite -> spriteRect.x &&
        abs(sprite -> spriteRect.y - playerY) < 100)
    {
        shootNextUpdate = true;
        direction = -1;
    }
    else if (playerX > sprite -> spriteRect.x &&
             abs(sprite -> spriteRect.y - playerY) < 100)
    {
        shootNextUpdate = true;
        direction = 1;
    }
    if (playerY > sprite -> spriteRect.y)
    {
        shootNextUpdate = true;
        directionY = 1;
    }
    else
    {
        shootNextUpdate = true;
        directionY = -1;
    }
}