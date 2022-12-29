#pragma once
#include "Game.hpp"

class TextureManager {
    public:
        static SDL_Texture* loadTexture(const char* file_name);
        static void draw(SDL_Texture* texture, SDL_Rect src_rect, SDL_Rect dst_rect, SDL_RendererFlip flip);
};