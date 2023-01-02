#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* texture) {
    SDL_Surface* temp_surface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    return tex;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect src_rect, SDL_Rect dst_rect, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, texture, &src_rect, &dst_rect, 0.0, NULL, flip);
}