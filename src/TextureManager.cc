#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager() { }

TextureManager::~TextureManager()
{
    for (std::pair<std::string, SDL_Texture*> p : loadedTextures)
    {
        SDL_DestroyTexture(p.second);
    }
}

SDL_Texture* TextureManager::loadTexture(std::string path, SDL_Renderer* renderer)
{
    SDL_Surface* temp = IMG_Load(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (temp != nullptr)
    {
        SDL_FreeSurface(temp);
        return texture;
    }
    else if (path != "")
    {
        std::cerr << "Unable to load image " << path << std::endl;
    }
}

SDL_Texture* TextureManager::findIfExists(std::string path)
{
    for (std::pair<std::string, SDL_Texture*> p : loadedTextures)
    {
        if (p.first == path)
        {
            return p.second;
        }
    }
    return nullptr;
}

SDL_Texture* TextureManager::getTexture(std::string path, SDL_Renderer* renderer)
{
    SDL_Texture* ptr = findIfExists(path);
    if (ptr != nullptr)
    {
        return ptr;
    }
    else
    {
        SDL_Texture* result = loadTexture(path, renderer);
        loadedTextures.push_back(std::make_pair(path, result));
        return result;
    }
}