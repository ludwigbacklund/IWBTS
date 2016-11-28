#ifndef MRRABBIT_H
#define MRRABBIT_H

#include "Enemy.h"
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "MrRabbitProjectile.h"

class MrRabbit : public Enemy
{
public:
    MrRabbit(int x_pos, int y_pos, SDL_Renderer* render, Player* player_ptr, TextureManager* mngr);

    void update(float const& deltaTime);
    void decideAction();
    void createObject(std::vector<GameObject*> &map_objects);
    void willCollide(std::vector<GameObject*> const& objects);

private:
    void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects);
    bool shootNextUpdate{false};
    double timeSinceShot{0};
    double updateTime{0};
};

#endif /* MRRABBIT_H */