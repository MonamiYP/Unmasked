#include "Game.hpp"

Game::Game() {

}

Game::~Game() {

}

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
        if(renderer)
            std::cout << "Renderer created successfully" << std::endl;
        
        is_running = true;
    } else {
        is_running = false;
    }
}

void Game::handleEvents() {

}

void Game::update() {

}

void Game::render() {

}

void Game::clean() {

}

bool Game::running() {
    return is_running;
}