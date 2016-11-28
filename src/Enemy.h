#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Player.h"

class Enemy : public GameObject
{
public:
    Enemy(int x_p, int y_p, int w, int h, int amountOfFrames, std::string spriteSheet, SDL_Renderer* render, Player* player_ptr, TextureManager* mngr);
    ~Enemy();

    virtual void decideAction() = 0;
    void moveLeft();
    void moveRight();

protected:
    Player* player;
};

#endif