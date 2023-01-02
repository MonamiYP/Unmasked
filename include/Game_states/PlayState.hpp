#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameState.hpp"

class PlayState : public GameState {
    public:
        PlayState() {}

        void init();

        void pause();
        void resume();

        void handleEvents(Game* game);
        void update(Game* game);
        void render(Game* game);
        void clean();

        static PlayState* instance() {
            return &play_state;
        }

    private:
        static PlayState play_state;
};