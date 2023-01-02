#pragma once
#include "Game.hpp"

class GameState {
    public:
        GameState() {}

        virtual void init() {}

        virtual void pause() {}
        virtual void resume() {}

        virtual void handleEvents(Game* game) {}
        virtual void update(Game* game) {}
        virtual void render(Game* game) {}
        virtual void clean() {}

        void changeState(Game* game, GameState* game_state) {
            game->changeState(game_state);
        }
};