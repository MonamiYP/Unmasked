#include "Game_states/StartState.hpp"
#include "Game_states/PlayState.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

StartState StartState::start_state;

void StartState::init() {
    SDL_Surface* surface = IMG_Load("assets/start_screen.png");
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

	SDL_FreeSurface(surface);
}

void StartState::clean() {
    SDL_DestroyTexture(texture);
}

void StartState::handleEvents(Game* game) {
    if (game->event.type == SDL_KEYDOWN) {
        switch (game->event.key.keysym.sym) {
        case SDLK_SPACE:
            game->changeState(PlayState::instance());
            break;
    
        default:
            break;
        }
    }
}

void StartState::update(Game* game) {}
void StartState::pause() {}
void StartState::resume() {}

void StartState::render(Game* game) {
    SDL_RenderClear(game->renderer);
    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
    SDL_RenderPresent(game->renderer);
}