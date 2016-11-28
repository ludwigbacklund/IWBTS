#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include <array>
#include "Sprite.h"

class GameObject
{
public:
    GameObject(int x_p, int y_p, int w, int h,int amountOfFrames, std::string spriteSheet, SDL_Renderer* render, TextureManager* mngr);
    virtual ~GameObject();

    virtual void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4 > > > collidingObjects) = 0;
    virtual void willCollide(std::vector<GameObject*> const& objects) = 0;
    virtual void update(float const& deltaTime) = 0;

    virtual void createObject(std::vector<GameObject*> &map_objects);

    void updatePosition();
    void takeDmg();
    void updateGravity(float const& deltaTime);
    bool intersect(GameObject* const& a, std::array<std::string, 4> &result);
    void kill();

    std::string getType() const;
    double getXVel() const;
    void setXVel(int const& new_xvel);
    double getYVel() const;
    void setYVel(int const& new_yvel);
    bool getDying() const;
    int getDirection() const;
    int getHealth() const;

    int xPos;
    int yPos;
    bool collidedThisUpdate{false};
    Sprite* sprite;

protected:
    int direction{1};
    bool dieNextUpdate{false};
    double yVel{0};
    double xVel{0};
    int health{1};
    double airTime{0};
    std::string type{"GameObject"};

};

#endif