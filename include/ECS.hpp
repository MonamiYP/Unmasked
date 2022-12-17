/*
    Check https://austinmorlan.com/posts/entity_component_system/#source-code for more
    in depth explanation of implementing ECS
*/

#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Entity;
class Component;

// Each component type has its own ID
// The Signature stores the compo
using ComponentID = std::size_t;
const std::size_t MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

inline ComponentID getComponentID() {
    static ComponentID last_ID = 0;
    return last_ID++;
}

template <typename T>
inline ComponentID getComponentID() noexcept {
    // Will be on one begin with, then follow last_ID which is being incremented everytime this is called
    static ComponentID type_ID = getComponentID();
    return type_ID;
}

class Component {
    public:
        Entity* entity;

        // Some will be overriden when a Component object is created
        virtual void init() {}
        virtual void update() {}
        virtual void draw() {}
        virtual ~Component() {}
};

class Entity {
    private:
        bool active = true;
        std::vector<std::unique_ptr<Component>> components;

        ComponentArray component_array;
        Signature signature;

    public:
        void update () {
            for(auto& c : components) c->update();
            for(auto& c : components) c->draw();
        }

        void draw() {}
        bool isActive() { return active; }
        void destroy() { active = false; }

        template <typename T> 
        bool hasComponent() const {
            return signature[getComponentID<T>()];
        }

        template <typename T, typename... T_args>
        T& addComponent(T_args&&... m_args) { // rvalue reference
            T* c(new T(std::forward<T_args>(m_args)...));
            c->entity = this;
            std::unique_ptr<Component> u_ptr { c };
            components.emplace_back(std::move(u_ptr)); // Add rvalue reference of component to end of an entity's components array

            component_array[getComponentID<T>()] = c;
            signature[getComponentID<T>()] = true;

            c->init();
            return *c;
        }

        template <typename T>
        T& getComponent() const {
            auto ptr(component_array[getComponentID<T>()]);
            return *static_cast<T*>(ptr);
        }
};

class Manager {
    public:
        void update() { for(auto& e : entities) e->update(); }

        void draw() { for(auto& e : entities) e->draw(); }

        void refresh() {
            /* Removes all entities that are not active anymore
            remove_if -> transforms entities array by moving entities which satisfy
            the statement 'if it's not active' to the end of array */
            entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &m_entity) { 
                return !m_entity->isActive();
            }), std::end(entities));
        }

        Entity& addEntity() {
            Entity* e = new Entity();
            std::unique_ptr<Entity> u_ptr { e };
            entities.emplace_back(std::move(u_ptr)); // Add rvalue reference of entity to end of entities array
            return *e;
        }

    private:
        std::vector<std::unique_ptr<Entity>> entities;
};