#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    SDL_Texture* getTexture(std::string path, SDL_Renderer* renderer);

private:
    SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
    SDL_Texture* findIfExists(std::string path);

    std::vector<std::pair<std::string, SDL_Texture*>>loadedTextures;
};

#endif /* TEXTUREMANAGER_H */