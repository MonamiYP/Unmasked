#pragma once
#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureManager.hpp"

class SpriteComponent : public Component {
    public:
        SpriteComponent() = default;
        SpriteComponent(const char* sprite_path) {
            setTexture(sprite_path);
        }
        ~SpriteComponent() {
            SDL_DestroyTexture(texture);
        }
        void setTexture(const char* sprite_path) {
            texture = TextureManager::loadTexture(sprite_path);
        }
        void init() override {
            transform = &entity->getComponent<TransformComponent>();
            src_rect.x = src_rect.y = 0;
            src_rect.w = transform->width;
            src_rect.h = transform->height;
        }
        void update() override {
            dst_rect.x = static_cast<int>(transform->position.x);
            dst_rect.y = static_cast<int>(transform->position.y);
            dst_rect.w = transform->width * transform->scale;
            dst_rect.h = transform->height * transform->scale;
        }
        void draw() override {
            TextureManager::draw(texture, src_rect, dst_rect);
        }

    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect src_rect, dst_rect;
};