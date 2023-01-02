#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;
class GameState;

class Game {
    public:
        Game();
        ~Game();

        void init(const char* title, int width, int height, bool full_screen);
        
        void handleEvents();
        void update();
        bool running();
        void render();
        void clean();

        void changeState(GameState* game_state);
        void pushState(GameState* game_state);
        void popState();

        static SDL_Renderer* renderer;
        static SDL_Event event;
        static SDL_Rect camera;
        static AssetManager* assets;

        enum group_labels : std::size_t {
            group_map,
            group_player,
            group_enemy,
            group_collider
        };

    private:
        std::vector<GameState*> game_states;

        bool fullscreen;
        bool is_running;
        SDL_Window* window;
};