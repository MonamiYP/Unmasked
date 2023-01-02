#pragma once
#include <SDL2/SDL.h>

class ColliderComponent;

class Collision {
    public:
        static bool AABB(const SDL_Rect& rect_a, const SDL_Rect& rect_b); 
        static bool AABB(const ColliderComponent& col_a, const ColliderComponent& col_b);
};