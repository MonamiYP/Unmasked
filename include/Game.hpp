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

        static void addTile(int src_x, int src_y, int x_pos, int y_pos);
        static SDL_Renderer* renderer;
        static SDL_Event event;
        static std::vector<ColliderComponent*> colliders;
        static SDL_Rect camera;

    private:
        bool is_running;
        SDL_Window* window;
};