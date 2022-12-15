#pragma once
#include "Game.hpp"

class TextureManager {
    public:
        static SDL_Texture* loadTexture(const char* file_name, SDL_Renderer* renderer);
};