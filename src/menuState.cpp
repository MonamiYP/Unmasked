#include "Game_states/MenuState.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

MenuState MenuState::menu_state;

void MenuState::init() {
    SDL_Surface* surface = IMG_Load("assets/pause_menu.bmp");
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

	SDL_FreeSurface(surface);
}

void MenuState::clean() {
    SDL_DestroyTexture(texture);
}

void MenuState::handleEvents(Game* game) {
    if (game->event.type == SDL_KEYDOWN) {
        switch (game->event.key.keysym.sym) {
        case SDLK_SPACE:
            game->popState();
            break;
    
        default:
            break;
        }
    }
}

void MenuState::update(Game* game) {

}

void MenuState::pause() {}
void MenuState::resume() {}

void MenuState::render(Game* game) {
    SDL_RenderClear(game->renderer);
    SDL_RenderCopy(game->renderer, texture, NULL, NULL);
    SDL_RenderPresent(game->renderer);
}