#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* texture, SDL_Renderer* renderer) {
    SDL_Surface* temp_surface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    return tex;
}