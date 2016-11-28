#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Projectile.h"
#include "PlayerProjectile.h"
#include "ActiveBlock.h"
#include "Continuator.h"

class Player : public GameObject
{
public:
    Player(int x_pos,int y_pos,SDL_Renderer* render, TextureManager* mngr);
    ~Player();

    void handle(SDL_Event event, float deltaTime);
    void willCollide(std::vector<GameObject*> const& objects);
    void createObject(std::vector<GameObject*> &map_objects);
    void update(float const& deltaTime);
    std::string getNextSubLevel();
    bool shouldChangeSubLevel();

    int jumpPower{1};

private:
    void shoot();
    void jump(float const& deltaTime);
    void handleCollision(std::vector<std::pair<GameObject*, std::array<std::string, 4>>> collidingObjects);
    void setIdleAnimation();
    void moveLeft();
    void moveRight();
    void setRunningAnimation();

    bool shootNextUpdate{false};
    bool canShoot{true};
    std::string nextSubLevel{""};
    double timeSinceShot{0};
};

#endif