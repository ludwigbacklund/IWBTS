#ifndef SPEEDDEMON_H
#define SPEEDDEMON_H
#include "Enemy.h"
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
class SpeedDemon : public Enemy
{
public:
    SpeedDemon(int x_pos,int y_pos,SDL_Renderer* render, Player* player_ptr, TextureManager* mngr);
    void update(float const& deltaTime);
    void willCollide(std::vector<GameObject*> const& objects);
    void decideAction();

private:
    void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects);
    void running();
    void idle();
};

#endif /* SPEEDDEMON_H */