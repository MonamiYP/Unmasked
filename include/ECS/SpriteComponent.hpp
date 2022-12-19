#pragma once
#include "Components.hpp"
#include "SDL2/SDL.h"

class SpriteComponent : public Component {
    public:
        SpriteComponent() = default;
        SpriteComponent(const char* sprite_path) {
            setTexture(sprite_path);
        }
        void setTexture(const char* sprite_path) {
            texture = TextureManager::loadTexture(sprite_path);

        }
        void init() override {
            transform = &entity->getComponent<TransformComponent>();
            src_rect.x = src_rect.y = 0;
            src_rect.w = src_rect.h = 32;
            dst_rect.w = dst_rect.h = 64;
        }
        void update() override {
            dst_rect.x = (int)transform->position.x;
            dst_rect.y = (int)transform->position.y;
        }
        void draw() override {
            TextureManager::draw(texture, src_rect, dst_rect);
        }

    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect src_rect, dst_rect;
};