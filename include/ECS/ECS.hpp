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
class Manager;

// Each component type has its own ID
// The component_signature stores the components an entity has, e.g 0,0,1,0,1 where 1 means it has the component with that ID
// Similar thing with groups; each entity has its own group signature
using ComponentID = std::size_t;
const std::size_t MAX_COMPONENTS = 32;
using ComponentSignature = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

using Group = std::size_t;
const std::size_t MAX_GROUPS = 32;
using GroupSignature = std::bitset<MAX_GROUPS>;

inline ComponentID getNewComponentID() {
    static ComponentID last_ID = 0u;
    return last_ID++;
}

template <typename T>
inline ComponentID getComponentID() noexcept {
    // Creating a component will call getComponentID() which returns the latest ID and then increases ID for any future components
    // When calling getComponentID() from a component that had already been created just returns the ID of the component
    static ComponentID type_ID = getNewComponentID();
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
        Manager& manager;
        bool active = true;
        std::vector<std::unique_ptr<Component>> components;

        ComponentArray component_array;
        ComponentSignature component_signature;
        GroupSignature group_signature;

    public:
        Entity(Manager& m_manager) : manager(m_manager) {

        }
        void update() { for(auto& c : components) c->update(); }

        void draw() { for(auto& c : components) c->draw(); }

        bool isActive() { return active; }
        void destroy() { active = false; }

        bool hasGroup(Group m_group) { return group_signature[m_group]; }

        void addGroup(Group m_group);
        void deleteGroup(Group m_group) {
            group_signature[m_group] = false;
        }

        template <typename T> 
        bool hasComponent() const {
            return component_signature[getComponentID<T>()];
        }

        template <typename T, typename... T_args>
        T& addComponent(T_args&&... m_args) { // rvalue reference
            T* c(new T(std::forward<T_args>(m_args)...));
            c->entity = this;
            std::unique_ptr<Component> u_ptr { c };
            components.emplace_back(std::move(u_ptr)); // Add rvalue reference of component to end of an entity's components array

            component_array[getComponentID<T>()] = c;
            component_signature[getComponentID<T>()] = true;

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
    private:
        std::vector<std::unique_ptr<Entity>> entities;
        std::array<std::vector<Entity*>, MAX_GROUPS> grouped_entities;
    public:
        void update() { for(auto& e : entities) e->update(); }

        void draw() { for(auto& e : entities) e->draw(); }

        void refresh() {
            // Remove entity from group if not active or not in group
            for (unsigned int i(0u); i < MAX_GROUPS; i++) {
                auto& v(grouped_entities[i]);
                v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* m_entity) {
                    return !m_entity->isActive() || !m_entity->hasGroup(i);
                }), std::end(v)); 
            }

            /* Removes all entities that are not active anymore
            remove_if -> transforms entities array by moving entities which satisfy
            the statement 'if it's not active' to the end of array */
            entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &m_entity) { 
                return !m_entity->isActive();
            }), std::end(entities));
        }

        void addToGroup(Entity* m_entity, Group m_group) {
            grouped_entities[m_group].emplace_back(m_entity);
        }

        std::vector<Entity*>& getGroup(Group m_group) {
            return grouped_entities[m_group];
        }

        Entity& addEntity() {
            Entity* e = new Entity(*this);
            std::unique_ptr<Entity> u_ptr { e };
            entities.emplace_back(std::move(u_ptr)); // Add rvalue reference of entity to end of entities array
            return *e;
        }
};

inline void Entity::addGroup(Group m_group) {
    group_signature[m_group] = true;
    manager.addToGroup(this, m_group);
}