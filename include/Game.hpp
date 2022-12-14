#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game {
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool full_screen);
        
        void handleEvents();
        void update();
        void render();
        void clean();

        bool running();

    private:
        bool is_running;
        SDL_Window* window;
        SDL_Renderer* renderer;
};