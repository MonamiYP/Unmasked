#include "Game.hpp"
#include "Game_states/StartState.hpp"

Game* game = nullptr;

int main(int argc, const char* argv[]) {
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;

    Uint32 frame_start;
    int frame_time;

    game = new Game();
    game->init("Unmasked", 800, 640, false);
    game->changeState(StartState::instance());

    while(game->running()) {
        frame_start = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frame_time = SDL_GetTicks() - frame_start;

        if(frame_delay > frame_time)
            SDL_Delay(frame_delay - frame_time);
    }

    game->clean();
}