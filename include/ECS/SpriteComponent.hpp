/*
    To do: 
    - Move the creation of animations into animation component
    - Pass map of animations to sprite component
    - So that different entities can have different animations
*/

#pragma once
#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include <map>

class SpriteComponent : public Component {
    public:
        int animation_index = 0;

        std::map<const char*, Animation> animations;

        SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

        SpriteComponent() = default;
        SpriteComponent(const char* sprite_path) {
            setTexture(sprite_path);
        }
        SpriteComponent(const char* sprite_path, bool is_animated) {
            animated = is_animated;

            Animation idle = Animation(0, 1, 100);
            Animation walk = Animation(0, 1, 100);
            Animation wiggle = Animation(0, 6, 200);

            animations.emplace("idle", idle);
            animations.emplace("walk", walk);
            animations.emplace("wiggle", wiggle);

            play("wiggle");

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
            if (animated) {
                src_rect.x = src_rect.w * static_cast<int>((SDL_GetTicks() / animation_speed) % animation_frames);
            }
            src_rect.y = animation_index * transform->height;

            dst_rect.x = static_cast<int>(transform->position.x) - Game::camera.x;
            dst_rect.y = static_cast<int>(transform->position.y) - Game::camera.y;
            dst_rect.w = transform->width * transform->scale;
            dst_rect.h = transform->height * transform->scale;
        }
        void draw() override {
            TextureManager::draw(texture, src_rect, dst_rect, sprite_flip);
        }
        void play(const char* animation_name) {
            animation_frames = animations[animation_name].frames;
            animation_index = animations[animation_name].index;
            animation_speed = animations[animation_name].speed;
        }

    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect src_rect, dst_rect;

        bool animated = false;
        int animation_frames = 0;
        int animation_speed = 100;
};