#pragma once
#include "GameState.hpp"

class MenuState : public GameState {
     public:
        SDL_Texture* texture;
        
        MenuState() {}

        void init();

        void pause();
        void resume();

        void handleEvents(Game* game);
        void update(Game* game);
        void render(Game* game);
        void clean();

        static MenuState* instance() {
            return &menu_state;
        }

    private:
        static MenuState menu_state;
};