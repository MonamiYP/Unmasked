#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;

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

        static void addTile(int x, int y, int id);
        static SDL_Renderer* renderer;
        static SDL_Event event;
        static std::vector<ColliderComponent*> colliders;

    private:
        bool is_running;
        SDL_Window* window;
};