#ifndef CONTINUATOR_H
#define CONTINUATOR_H
#include "ActiveBlock.h"
class Continuator : public ActiveBlock
{
public:
    Continuator(int x, int y, SDL_Renderer* render,std::string path, TextureManager* mngr);

    void activate();
    std::string getSubLevelPath();

private:
    std::string subLevelPath;
};
#endif