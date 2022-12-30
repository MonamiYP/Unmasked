#pragma once
#include "Components.hpp"
#include "SDL2/SDL.h"

class TileComponent : public Component {
    public:
        SDL_Texture* texture;
        SDL_Rect src_rect, dst_rect;
        Vector2D position;

        TileComponent() = default;
        ~TileComponent() {
            SDL_DestroyTexture(texture);
        }
        TileComponent(int src_x, int src_y, int x_pos, int y_pos, const char* path) {
            texture = TextureManager::loadTexture(path);

            position.x = x_pos;
            position.y = y_pos;

            src_rect.x = src_x;
            src_rect.y = src_y;
            src_rect.w = src_rect.h = 32;

            dst_rect.x = x_pos;
            dst_rect.y = y_pos;
            dst_rect.w = dst_rect.h = 32;
        }
        void update() override {
            dst_rect.x = position.x - Game::camera.x;
            dst_rect.y = position.y - Game::camera.y;
        }
        void draw() override {
            TextureManager::draw(texture, src_rect, dst_rect, SDL_FLIP_NONE);
        }
};