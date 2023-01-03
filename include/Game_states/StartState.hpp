#pragma once
#include "GameState.hpp"

class StartState : public GameState {
     public:
        SDL_Texture* texture;
        
        StartState() {}

        void init();

        void pause();
        void resume();

        void handleEvents(Game* game);
        void update(Game* game);
        void render(Game* game);
        void clean();

        static StartState* instance() {
            return &start_state;
        }

    private:
        static StartState start_state;
};