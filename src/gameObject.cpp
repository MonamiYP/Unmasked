#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texture_sheet, int x, int y) {
    obj_texture = TextureManager::loadTexture(texture_sheet);

    x_pos = x;
    y_pos = y;
}

void GameObject::update() {
    x_pos++;
    y_pos++;

    src_rect.w = 32;
    src_rect.h = 32;
    src_rect.x = 0;
    src_rect.y = 0;

    dst_rect.w = src_rect.w * 2;
    dst_rect.h = src_rect.h * 2;
    dst_rect.x = x_pos;
    dst_rect.y = y_pos;
}

void GameObject::render() {
    SDL_RenderCopy(Game::renderer, obj_texture, &src_rect, &dst_rect);
}