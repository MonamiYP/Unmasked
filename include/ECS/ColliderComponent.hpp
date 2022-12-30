#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "Components.hpp"
#include "../TextureManager.hpp"

class ColliderComponent : public Component {
    public:
        SDL_Rect collider;
        std::string tag;

        SDL_Texture* texture;
        SDL_Rect src_rect, dst_rect;

        TransformComponent* transform;

        ColliderComponent(std::string t) {
            tag = t;
        }
        ColliderComponent(std::string t, int x_pos, int y_pos) {
            tag = t;
            collider.x = x_pos;
            collider.y = y_pos;
            collider.h = collider.w = 32;
        }

        void init() override {
            if(!entity->hasComponent<TransformComponent>()) {
                entity->addComponent<TransformComponent>();
            }
            transform = &entity->getComponent<TransformComponent>();

            texture = TextureManager::loadTexture("assets/collider_box.png");
            src_rect = { 0,0,32,32 };
            dst_rect = { collider.x, collider.y, collider.w, collider.h };
        }
        void draw() override {
            TextureManager::draw(texture, src_rect, dst_rect, SDL_FLIP_NONE);
        }
        void update() override {
            if(tag != "terrain") {
                collider.x = static_cast<int>(transform->position.x);
                collider.y = static_cast<int>(transform->position.y);
                collider.w = transform->width * transform->scale;
                collider.h = transform->height * transform->scale;
            }

            dst_rect.x = collider.x - Game::camera.x;
            dst_rect.y = collider.y - Game::camera.y;
        }
};