#ifndef SKELETRON_H
#define SKELETRON_H

#include "Enemy.h"
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <random>
#include "MrRabbitProjectile.h"

class Skeletron : public Enemy
{
public:
    Skeletron(int x_pos, int y_pos, SDL_Renderer* render, Player* player_ptr, ActiveBlock* target_obj, TextureManager* mngr);
    ~Skeletron();

    void update(float const& deltaTime);
    void decideAction();
    void createObject(std::vector<GameObject*> &map_objects);
    void willCollide(std::vector<GameObject*> const& objects);

private:
    void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects);

    bool shootNextUpdate{false};
    double timeSinceShot{0};
    double timeToTP{0};
    bool willTp{false};
    ActiveBlock* dropOnDeath;
    std::random_device rnd;
    std::uniform_int_distribution<int> tp{1,780};
    std::uniform_int_distribution<int> action{1,200};
    int directionY{0};
    Sprite* tpIndicator;
    Sprite* healthbar;
};

#endif /* SKELETRON */