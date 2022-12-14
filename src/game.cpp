#include "Game.hpp"

SDL_Texture* player_texture;
SDL_Rect src_rect, des_rect;

Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool full_screen) {
    int flags = 0;
    if(full_screen)
        flags = SDL_WINDOW_FULLSCREEN;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL_Init successful" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window)
            std::cout << "Window created successfully" << std::endl;
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 50, 50, 100, 255);
            std::cout << "Renderer created successfully" << std::endl;
        }
        
        is_running = true;
    }

    SDL_Surface* temp_surface = IMG_Load("assets/player.png");
    player_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    des_rect.h = 64;
    des_rect.w = 64;
}

void Game::render() {
    SDL_RenderClear(renderer);
    // Add stuff to render here
    SDL_RenderCopy(renderer, player_texture, NULL, &des_rect);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleared" << std::endl;
}

bool Game::running() {
    return is_running;
}