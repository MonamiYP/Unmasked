#include "Collision.hpp"
#include "ECS/ColliderComponent.hpp"
#include <iostream>

bool Collision::AABB(const SDL_Rect& rect_a, const SDL_Rect& rect_b) {
    return SDL_HasIntersection(&rect_a, &rect_b);
}

bool Collision::AABB(const ColliderComponent& col_a, const ColliderComponent& col_b) {
    if( AABB(col_a.collider, col_b.collider) ) {
        return true;
    } return false;
}