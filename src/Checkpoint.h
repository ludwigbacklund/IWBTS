#ifndef CHECKPOINT_H
#define CHECKPOINT_H
#include "GameObject.h"

class Checkpoint : public GameObject
{
public:
    Checkpoint(int x_pos, int y_pos, SDL_Renderer* render, TextureManager* mngr);
    ~Checkpoint();

    void update(float const& deltaTime);
    void willCollide(std::vector<GameObject*> const& objects);

private:
    void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects);
};

#endif