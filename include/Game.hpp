#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

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

        static SDL_Renderer* renderer;
        static SDL_Event event;

    private:
        bool is_running;
        SDL_Window* window;
};